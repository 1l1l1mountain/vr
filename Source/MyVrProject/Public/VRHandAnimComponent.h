#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "VRHandAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UVRHandAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRHandAnimComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*>inputs);
	
private:
	class AVR_Player* player;
	//class UVRHandAnimInstance* handAnim;
	class UVRHandAnimInstance* handAnim_Left;
	class UVRHandAnimInstance* handAnim_Right;

	void InputIndexTriggerValue_Left(const FInputActionValue& value);
	void InputGripValue_Left(const FInputActionValue& value);
	void InputIndexTriggerTouch_Left(const FInputActionValue& value);
	void InputThumbstickTouch_Left(const FInputActionValue& value);


	void InputIndexTriggerValue_Right(const FInputActionValue& value);
	void InputGripValue_Right(const FInputActionValue& value);
	void InputIndexTriggerTouch_Right(const FInputActionValue& value);
	void InputThumbstickTouch_Right(const FInputActionValue& value);
};
