// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithPlayerStart.h"
#include "WraithPlayerData.h"

const UWraithInputConfig* AWraithPlayerStart::GetPlayerInputConfig() const
{
	return PlayerData ? PlayerData->InputConfig : nullptr;
}

const UWraithCharacterDescription* AWraithPlayerStart::GetPlayerCharacterDescription() const
{
	return PlayerData ? PlayerData->PlayerCharacterDescription : nullptr;
}
