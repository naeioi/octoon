#include "gl33_texture.h"
#include "gl33_device.h"

namespace octoon
{
	namespace hal
	{
		OctoonImplementSubClass(GL33Texture, GraphicsTexture, "GL33Texture")

		GL33Texture::GL33Texture() noexcept
			: _target(GL_INVALID_ENUM)
			, _pbo(GL_NONE)
			, _pboSize(0)
			, _upbo(GL_NONE)
			, _upboSize(0)
			, _texture(GL_NONE)
		{
		}

		GL33Texture::~GL33Texture() noexcept
		{
			this->close();
		}

		bool
		GL33Texture::setup(const GraphicsTextureDesc& textureDesc) noexcept
		{
			assert(_texture == GL_NONE);

			GLenum target = GL33Types::asTextureTarget(textureDesc.getTexDim());
			if (target == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid texture target");
				return false;
			}

			GLenum internalFormat = GL33Types::asTextureInternalFormat(textureDesc.getTexFormat());
			if (internalFormat == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid texture internal format.");
				return false;
			}

			glGenTextures(1, &_texture);
			if (_texture == GL_NONE)
			{
				this->getDevice()->downcast<GL33Device>()->message("glGenTextures() fail");
				return false;
			}

			glBindTexture(target, _texture);

			GLsizei width = (GLsizei)textureDesc.getWidth();
			GLsizei height = (GLsizei)textureDesc.getHeight();
			GLsizei depth = (GLsizei)textureDesc.getDepth();

			GLsizei mipBase = textureDesc.getMipBase();
			GLsizei mipLevel = textureDesc.getMipNums();

			if (target != GL_TEXTURE_2D_MULTISAMPLE && target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
			{
				GL_CHECK(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
				GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

				if (!applyMipmapLimit(target, mipBase, mipLevel))
					return false;
			}

			const char* stream = (const char*)textureDesc.getStream();
			if (GL33Types::isCompressedTexture(textureDesc.getTexFormat()))
			{
				std::size_t offset = 0;

				GLint oldPackStore = 1;
				glGetIntegerv(GL_UNPACK_ALIGNMENT, &oldPackStore);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 8);

				for (GLint mip = mipBase; mip < mipBase + mipLevel; mip++)
				{
					GLsizei w = std::max(width / (1 << mip), 1);
					GLsizei h = std::max(height / (1 << mip), 1);
					GLsizei mipSize = GL33Types::getCompressedTextureSize(w, h, 1, internalFormat);
					if (mipSize > 0)
						glCompressedTexImage2D(GL_TEXTURE_2D, mip, internalFormat, w, h, 0, mipSize, (char*)stream + offset);
					else
						this->getDevice()->downcast<GL33Device>()->message("bad texformat in compressed_texture_size");

					offset += stream ? mipSize : 0;
				}

				glPixelStorei(GL_UNPACK_ALIGNMENT, oldPackStore);
			}
			else
			{
				GLenum format = GL33Types::asTextureFormat(textureDesc.getTexFormat());
				if (format == GL_INVALID_ENUM)
				{
					this->getDevice()->downcast<GL33Device>()->message("Invalid texture format");
					return false;
				}

				GLenum type = GL33Types::asTextureType(textureDesc.getTexFormat());
				if (type == GL_INVALID_ENUM)
				{
					this->getDevice()->downcast<GL33Device>()->message("Invalid texture type");
					return false;
				}

				GLsizei offset = 0;
				GLsizei pixelSize = stream ? GL33Types::getFormatNum(format, type) : 1;

				GLint oldPackStore = 1;
				glGetIntegerv(GL_UNPACK_ALIGNMENT, &oldPackStore);

				if (pixelSize == 1)
					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				else if (pixelSize == 2)
					glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
				else if (pixelSize == 4 || pixelSize == 12)
					glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				else if (pixelSize == 8 || pixelSize == 16)
					glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
				else
					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				if (target == GL_TEXTURE_2D_MULTISAMPLE || target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
				{
					if (target == GL_TEXTURE_2D_MULTISAMPLE)
						glTexImage2DMultisample(target, textureDesc.getTexMultisample(), internalFormat, width, height, GL_FALSE);
					else
					{
						GLsizei layerBase = textureDesc.getLayerBase() + 1;
						GLsizei layerLevel = textureDesc.getLayerNums();

						for (GLsizei layer = layerBase; layer < layerBase + layerLevel; layer++)
							glTexImage3DMultisample(_texture, textureDesc.getTexMultisample(), internalFormat, width, height, layer, GL_FALSE);
					}
				}
				else
				{
					for (GLsizei mip = mipBase; mip < mipBase + mipLevel; mip++)
					{
						GLsizei w = std::max(width / (1 << mip), 1);
						GLsizei h = std::max(height / (1 << mip), 1);
						GLsizei mipSize = w * h * pixelSize;
						GLsizei layerBase = textureDesc.getLayerBase();
						GLsizei layerLevel = textureDesc.getLayerNums();

						for (GLsizei layer = layerBase; layer < layerBase + layerLevel; layer++)
						{
							if (target == GL_TEXTURE_2D)
							{
								glTexImage2D(target, mip, internalFormat, w, h, 0, format, type, stream ? stream + offset : nullptr);
							}
							else
							{
								if (target == GL_TEXTURE_CUBE_MAP_ARRAY ||
									target == GL_TEXTURE_CUBE_MAP)
								{
									GLenum cubeFace[] =
									{
										GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
										GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
										GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
									};

									for (GLsizei face = 0; face < 6; face++)
									{
										if (target == GL_TEXTURE_CUBE_MAP)
											glTexImage2D(cubeFace[face], mip, internalFormat, w, h, 0, format, type, stream ? (char*)stream + offset : nullptr);
										else
											glTexImage3D(cubeFace[face], mip, internalFormat, w, h, layer + 1, 0, format, type, stream ? (char*)stream + offset : nullptr);

										offset += mipSize;
									}
								}
								else
								{
									if (target == GL_TEXTURE_2D_ARRAY)
										glTexImage3D(target, mip, internalFormat, w, h, layer + 1, 0, format, type, stream ? (char*)stream + offset : nullptr);
									else
										glTexImage3D(target, mip, internalFormat, w, h, depth, 0, format, type, stream ? (char*)stream + offset : nullptr);

									offset += mipSize;
								}
							}
						}
					}
				}

				glPixelStorei(GL_UNPACK_ALIGNMENT, oldPackStore);
			}

			glBindTexture(target, GL_NONE);

			_target = target;
			_textureDesc = textureDesc;

			return GL33Check::checkError();
		}

		void
		GL33Texture::close() noexcept
		{
			if (_texture != GL_NONE)
			{
				glDeleteTextures(1, &_texture);
				_texture = GL_NONE;
			}

			if (_pbo != GL_NONE)
			{
				glDeleteBuffers(1, &_pbo);
				_pbo = GL_NONE;
			}

			if (_upbo != GL_NONE)
			{
				glDeleteBuffers(1, &_upbo);
				_upbo = GL_NONE;
			}
		}

		bool
		GL33Texture::map(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h, std::uint32_t mipLevel, void** data) noexcept
		{
			assert(data);

			GLenum format = GL33Types::asTextureFormat(_textureDesc.getTexFormat());
			if (format == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid texture format");
				return false;
			}

			GLenum type = GL33Types::asTextureType(_textureDesc.getTexFormat());
			if (type == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid texture type");
				return false;
			}

			if (type == GL_HALF_FLOAT)
				type = GL_FLOAT;

			GLsizei num = GL33Types::getFormatNum(format, type);
			if (num == 0)
				return false;

			if (_pbo == GL_NONE)
				glGenBuffers(1, &_pbo);

			glBindBuffer(GL_PIXEL_PACK_BUFFER, _pbo);

			GLsizei mapSize = _textureDesc.getWidth() * _textureDesc.getHeight() * num;
			if (_pboSize < mapSize)
			{
				glBufferData(GL_PIXEL_PACK_BUFFER, mapSize, nullptr, GL_STREAM_READ);
				_pboSize = mapSize;
			}

			glBindTexture(_target, _texture);
			glGetTexImage(_target, mipLevel, format, type, 0);

			*data = glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, mapSize, GL_MAP_READ_BIT);
			(std::uint8_t*&)*data += (y * _textureDesc.getWidth() * num) + x * num;

			return *data ? true : false;
		}

		void
		GL33Texture::unmap() noexcept
		{
			glBindBuffer(GL_PIXEL_PACK_BUFFER, _pbo);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}

		GLenum
		GL33Texture::getTarget() const noexcept
		{
			return _target;
		}

		GLuint
		GL33Texture::getInstanceID() const noexcept
		{
			return _texture;
		}

		bool
		GL33Texture::applyMipmapLimit(GLenum target, std::uint32_t min, std::uint32_t count) noexcept
		{
			glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, min);
			glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, min + count - 1);
			return true;
		}

		bool
		GL33Texture::applySamplerWrap(GLenum target, GraphicsSamplerWrap wrap) noexcept
		{
			GLenum glwrap = GL33Types::asSamplerWrap(wrap);
			if (glwrap == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid sampler wrap");
				return false;
			}

			glTexParameteri(target, GL_TEXTURE_WRAP_S, glwrap);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, glwrap);
			glTexParameteri(target, GL_TEXTURE_WRAP_R, glwrap);

			return true;
		}

		bool
		GL33Texture::applySamplerFilter(GLenum target, GraphicsSamplerFilter minFilter, GraphicsSamplerFilter magFilter) noexcept
		{
			GLenum min = GL33Types::asSamplerMinFilter(minFilter);
			GLenum mag = GL33Types::asSamplerMagFilter(magFilter);
			if (min == GL_INVALID_ENUM || mag == GL_INVALID_ENUM)
			{
				this->getDevice()->downcast<GL33Device>()->message("Invalid sampler filter");
				return false;
			}

			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min);
			glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag);
			return true;
		}

		bool
		GL33Texture::applySamplerAnis(GLenum target, GraphicsSamplerAnis anis) noexcept
		{
			if (GLEW_EXT_texture_filter_anisotropic)
			{
				if (anis == GraphicsSamplerAnis::Anis1)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
				else if (anis == GraphicsSamplerAnis::Anis2)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2);
				else if (anis == GraphicsSamplerAnis::Anis4)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
				else if (anis == GraphicsSamplerAnis::Anis8)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
				else if (anis == GraphicsSamplerAnis::Anis16)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
				else if (anis == GraphicsSamplerAnis::Anis32)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 32);
				else if (anis == GraphicsSamplerAnis::Anis64)
					glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 64);
			}

			return true;
		}

		const std::uint64_t
		GL33Texture::handle() const noexcept
		{
			return _texture;
		}

		const GraphicsTextureDesc&
		GL33Texture::getTextureDesc() const noexcept
		{
			return _textureDesc;
		}

		void
		GL33Texture::setDevice(const GraphicsDevicePtr& device) noexcept
		{
			_device = device;
		}

		GraphicsDevicePtr
		GL33Texture::getDevice() noexcept
		{
			return _device.lock();
		}
	}
}