#ifndef OCTOON_KEYFRAME_H_
#define OCTOON_KEYFRAME_H_

#include <octoon/animation/interpolator.h>
#include <memory>
#include <vector>

namespace octoon
{
	namespace animation
	{
		template<typename _Elem = float, typename _Time = float>
		class Keyframe final
		{
		public:
			_Time time;
			_Elem value;
			std::shared_ptr<Interpolator<_Time>> interpolator;

			Keyframe() noexcept
				: time()
				, value()
			{
			}

			Keyframe(const _Time& time_, const _Elem& value_, std::shared_ptr<Interpolator<_Time>>&& interpolator_ = nullptr) noexcept
				: time(time_)
				, value(value_)
				, interpolator(std::move(interpolator_))
			{
			}

			Keyframe(_Time&& time_, _Elem&& value_, std::shared_ptr<Interpolator<_Time>>&& interpolator_ = nullptr) noexcept
				: time(std::move(time_))
				, value(std::move(value_))
				, interpolator(std::move(interpolator_))
			{
			}

			~Keyframe() noexcept
			{
			}

		public:
			friend Keyframe& operator+=(Keyframe& a, const Keyframe& b) noexcept
			{
				a.time += b.time;
				a.value += b.value;
				return a;
			}

			friend Keyframe& operator-=(Keyframe& a, const Keyframe& b) noexcept
			{
				a.time -= b.time;
				a.value -= b.value;
				return a;
			}

			friend Keyframe& operator*=(Keyframe& a, const Keyframe& b) noexcept
			{
				a.time *= b.time;
				a.value *= b.value;
				return a;
			}

			friend Keyframe& operator/=(Keyframe& a, const Keyframe& b) noexcept
			{
				a.time /= b.time;
				a.value /= b.value;
				return a;
			}

			friend Keyframe operator+(const Keyframe& a, const Keyframe& b) noexcept
			{
				return Keyframe(a.time + b.time, a.value + b.value);
			}

			friend Keyframe operator-(const Keyframe& a, const Keyframe& b) noexcept
			{
				return Keyframe(a.time - b.time, a.value - b.value);
			}

			friend Keyframe operator*(const Keyframe& a, const Keyframe& b) noexcept
			{
				return Keyframe(a.time * b.time, a.value * b.value);
			}

			friend Keyframe operator/(const Keyframe& a, const Keyframe& b) noexcept
			{
				return Keyframe(a.time / b.time, a.value / b.value);
			}
		};

		template<typename _Elem = float, typename _Time = float>
		using Keyframes = std::vector<Keyframe<_Elem, _Time>>;
	}
}

#endif