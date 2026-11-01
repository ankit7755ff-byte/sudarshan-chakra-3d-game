#include "Sudarshan.h"

DEFINE_LOG_CATEGORY(LogSudarshan);

void FSudarshanModule::StartupModule()
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Core Game Module Initialized successfully."));
}

void FSudarshanModule::ShutdownModule()
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Core Game Module Shutdown."));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FSudarshanModule, Sudarshan, "Sudarshan");
