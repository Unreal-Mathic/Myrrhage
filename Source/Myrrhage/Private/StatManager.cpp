// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "StatManager.h"

UStatManager::UStatManager()
{
	InitializeStats();
}

void UStatManager::InitializeStats()
{
	Agility = FStatStruct(EStat::EAgility);
	Knowledge = FStatStruct(EStat::EKnowledge);
	Might = FStatStruct(EStat::EMight);
	Presence = FStatStruct(EStat::EPresence);
	Resistance = FStatStruct(EStat::EResistance);
}

FString UStatManager::GetCharacterStats()
{
	FString stats;
	stats += Agility.GetEnumAsString() + " ";
	stats += Knowledge.GetEnumAsString() + " ";
	stats += Might.GetEnumAsString() + " ";
	stats += Presence.GetEnumAsString() + " ";
	stats += Resistance.GetEnumAsString();
	return stats;
}

void UStatManager::CalculateStats(class ABaseEquipment* Equipment)
{

}

void UStatManager::AddStats(class ABaseEquipment* Equipment)
{
	TArray<FStatStruct> Stats = Equipment->GetStats();
	for (int32 stat = 0; stat < Stats.Num(); stat++)
	{
		switch (Stats[stat].GetType())
		{
		case EStat::EAgility:
			Agility.AddToValue(Stats[stat].GetValue());
			break;
		case EStat::EKnowledge:
			Knowledge.AddToValue(Stats[stat].GetValue());
			break;
		case EStat::EMight:
			Might.AddToValue(Stats[stat].GetValue());
			break;
		case EStat::EPresence:
			Presence.AddToValue(Stats[stat].GetValue());
			break;
		case EStat::EResistance:
			Resistance.AddToValue(Stats[stat].GetValue());
			break;
		default:
			break;
		}
	}
}

void UStatManager::RemoveStats(class ABaseEquipment* Equipment)
{
	TArray<FStatStruct> Stats = Equipment->GetStats();
	for (int32 stat = 0; stat < Stats.Num(); stat++)
	{
		switch (Stats[stat].GetType())
		{
		case EStat::EAgility:
			Agility.SubtractFromValue(Stats[stat].GetValue());
			break;
		case EStat::EKnowledge:
			Knowledge.SubtractFromValue(Stats[stat].GetValue());
			break;
		case EStat::EMight:
			Might.SubtractFromValue(Stats[stat].GetValue());
			break;
		case EStat::EPresence:
			Presence.SubtractFromValue(Stats[stat].GetValue());
			break;
		case EStat::EResistance:
			Resistance.SubtractFromValue(Stats[stat].GetValue());
			break;
		default:
			break;
		}
	}
}
