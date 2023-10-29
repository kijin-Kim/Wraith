// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithButtonWidget.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"

void UWraithButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	NormalStyleCached = GenericButton->GetStyle().Normal;
	HoveredStyleCached = GenericButton->GetStyle().Hovered;

	RootSizeBox->SetWidthOverride(Width);
	RootSizeBox->SetHeightOverride(Height);
	
	SetIsFocusable(true);
}

void UWraithButtonWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	if (!IsHovered())
	{
		FButtonStyle Style = GenericButton->GetStyle();
		Style.Normal = HoveredStyleCached;
		GenericButton->SetStyle(Style);
	}
}

void UWraithButtonWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	if (!IsHovered())
	{
		FButtonStyle Style = GenericButton->GetStyle();
		Style.Normal = NormalStyleCached;
		GenericButton->SetStyle(Style);
	}
}
