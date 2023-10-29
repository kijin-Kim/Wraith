// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WraithUserWidget.h"
#include "WraithButtonWidget.generated.h"

class USizeBox;
class UButton;
/**
 * 
 */
UCLASS()
class WRAITH_API UWraithButtonWidget : public UWraithUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta= (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta= (BindWidget))
	TObjectPtr<UButton> GenericButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonWidget")
	float Width = 250.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonWidget")
	float Height = 50.0f;
	

private:
	FSlateBrush NormalStyleCached;
	FSlateBrush HoveredStyleCached;
};
