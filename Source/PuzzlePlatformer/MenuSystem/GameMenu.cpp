// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"

#include "Components/Button.h"

bool UGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// TODO: Setup
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::CancelMenu);
	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UGameMenu::QuitGame);

	return true;
}

void UGameMenu::CancelMenu() {
	if (MenuInterface != nullptr) {
		this->Teardown();
	}
};

void UGameMenu::QuitGame() {
	if (MenuInterface != nullptr) {
		Teardown();
		MenuInterface->QuitGame();
	}
};
