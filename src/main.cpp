#include "Conditions.h"

template <typename T>
void RegisterCondition()
{
	auto result = OAR_API::Conditions::AddCustomCondition<T>();
	switch (result)
	{
	case OAR_API::Conditions::APIResult::OK:
		logs::info("Registered {} condition!", T::CONDITION_NAME);
		break;
	case OAR_API::Conditions::APIResult::AlreadyRegistered:
		logs::warn("Condition {} is already registered!",
		           T::CONDITION_NAME);
		break;
	case OAR_API::Conditions::APIResult::Invalid:
		logs::error("Condition {} is invalid!", T::CONDITION_NAME);
		break;
	case OAR_API::Conditions::APIResult::Failed:
		logs::error("Failed to register condition {}!", T::CONDITION_NAME);
		break;
	}
}

void InitMessaging()
{
	const auto intfc = SKSE::GetMessagingInterface();
	if (!intfc->RegisterListener([](SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SKSE::MessagingInterface::kPostLoad)
		{
			OAR_API::Conditions::GetAPI(OAR_API::Conditions::InterfaceVersion::Latest);
			if (g_oarConditionsInterface)
			{
				RegisterCondition<Conditions::DialogueCondition>();
			}
			else
			{
				logs::error("Failed to request Open Animation Replacer API"sv);
			}
		}
	}))
	{
		stl::report_and_fail("Failed to initialize message listener.");
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	InitMessaging();
	logs::info("{} loaded.", SKSE::PluginDeclaration::GetSingleton()->GetName());
	return true;
}
