#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity{ ShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation =
			UKismetMathLibrary::MakeRotFromX(
				ShooterCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(
			MovementRotation,
			AimRotation).Yaw;

		//if (ShooterCharacter->GetVelocity().Size() > 0.f)
		//{
		//	LastMovementOffsetYaw = MovementOffsetYaw;
		//}

		bAiming = ShooterCharacter->GetAiming();

		/*
		FString RotationMessage =
			FString::Printf(
				TEXT("Base Aim Rotation: %f"),
				AimRotation.Yaw);*/

				/*
				FString MovementRotationMessage =
					FString::Printf(
						TEXT("Movement Rotation: %f"),
						MovementRotation.Yaw);*/
						
						//FString offsetmessage =
						//	FString::Printf(
						//		TEXT("movement offset yaw: %f"),
						//		MovementOffsetYaw);

						//	
						//		if (GEngine)
						//		{
						//			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, offsetmessage);
						//		}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}