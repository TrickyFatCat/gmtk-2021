﻿#pragma once

class Utils
{
public:
	template <typename T>
	static T* GetPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
	}

	template <typename T>
	static T* FindFirstNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;

		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			if (AnimNotify)
			{
				return AnimNotify;
			}
		}

		return nullptr;
	}
};
