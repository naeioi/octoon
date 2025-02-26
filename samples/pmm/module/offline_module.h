#ifndef MYSTICLIT_OFFLINE_MODULE_H_
#define MYSTICLIT_OFFLINE_MODULE_H_

#include <mysticLit_model.h>

namespace MysticLit
{
	class OfflineModule final : public MysticLitModule
	{
	public:
		OfflineModule() noexcept;
		virtual ~OfflineModule() noexcept;

		virtual void reset() noexcept override;

	private:
		OfflineModule(const OfflineModule&) = delete;
		OfflineModule& operator=(const OfflineModule&) = delete;

	public:
		bool offlineEnable;
	};
}

#endif