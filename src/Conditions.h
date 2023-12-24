#pragma once
#include "API/OpenAnimationReplacerAPI-Conditions.h"
#include "API/OpenAnimationReplacer-ConditionTypes.h"

namespace Conditions
{
	class DialogueCondition : public CustomCondition
	{
	public:
		// Mandatory stuff
		constexpr static inline std::string_view CONDITION_NAME = "Dialogue"sv;
		RE::BSString GetName() const override { return CONDITION_NAME.data(); }
		RE::BSString GetDescription() const override { return "Checks if various aspects related to dialogue are true."sv.data(); }
		constexpr REL::Version GetRequiredVersion() const override { return { 1, 0, 0 }; }

		void PostInitialize() override;

		IBoolConditionComponent* dialogueActive = static_cast<IBoolConditionComponent*>(AddBaseComponent(
			ConditionComponentType::kBool,
			"Trigger whenever dialogue is active."));
		IBoolConditionComponent* dialogueStarted = static_cast<IBoolConditionComponent*>(AddBaseComponent(
			ConditionComponentType::kBool,
			"Trigger when dialogue starts."));
		IBoolConditionComponent* playerChoosing = static_cast<IBoolConditionComponent*>(AddBaseComponent(
			ConditionComponentType::kBool,
			"Trigger when player is choosing."));
		IBoolConditionComponent* playerChose = static_cast<IBoolConditionComponent*>(AddBaseComponent(
			ConditionComponentType::kBool,
			"Trigger when player has chosen."));
		IBoolConditionComponent* dialogueEnded = static_cast<IBoolConditionComponent*>(AddBaseComponent(
			ConditionComponentType::kBool,
			"Trigger when dialogue ends."));

	protected:
		bool EvaluateImpl(RE::TESObjectREFR* a_refr, RE::hkbClipGenerator* a_clipGenerator) const override;

	private:
		mutable bool dialogueIsActive;
		mutable bool playersChoice;
	};
}