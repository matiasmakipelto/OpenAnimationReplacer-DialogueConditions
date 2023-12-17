#include "Conditions.h"


namespace Conditions
{
	void DialogueCondition::PostInitialize()
	{
		CustomCondition::PostInitialize();
		dialogueIsActive = false;
		playersChoice = false;
	}

	bool DialogueCondition::EvaluateImpl([[maybe_unused]] RE::TESObjectREFR* a_refr,
		[[maybe_unused]] RE::hkbClipGenerator* a_clipGenerator) const
	{
		RE::UI* ui = RE::UI::GetSingleton();
		RE::BSString dialogue = RE::BSString("Dialogue Menu");

		bool result = false;

		if (ui && ui->IsMenuOpen(dialogue)) {
			// Dialogue is active
			result |= dialogueActive->GetBoolValue();

			// Dialogue started
			if (!dialogueIsActive)
				result |= dialogueStarted->GetBoolValue();
			dialogueIsActive = true;

			// Players choise
			RE::MenuTopicManager* menuTopicManager = RE::MenuTopicManager::GetSingleton();
			if (menuTopicManager->currentTopicInfo == nullptr) {
				// Player choosing
				result |= playerChoosing->GetBoolValue();

				playersChoice = true;
			}
			else {
				// Player chose
				if (playersChoice)
					result |= playerChose->GetBoolValue();

				playersChoice = false;
			}
		}
		else {
			// Dialogue ended
			if (dialogueIsActive)
				result |= dialogueEnded->GetBoolValue();
			dialogueIsActive = false;
		}

		return result;
	}
}