// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSkill.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h" 
#include "Engine/World.h"

// Sets default values for this component's properties
UJumpSkill::UJumpSkill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJumpSkill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJumpSkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UJumpSkill::JumpSkill(AActor* Actor, bool bIsEnemy)
{
    if (!Actor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Actor passed to JumpSkill."));
        return false;
    }

    //
    FVector WStartLocation = Actor->GetActorLocation();
    FVector WForwardDirection = Actor->GetActorForwardVector();

    
    FVector WallTraceStart = WStartLocation + WForwardDirection * 100.0f; 
    FVector WallTraceEnd = WallTraceStart + WForwardDirection * 300.0f; 

    FHitResult WallHitResult;
    FCollisionQueryParams WallParams;
    WallParams.AddIgnoredActor(Actor);

   // DrawDebugLine(GetWorld(), WallTraceStart, WallTraceEnd, FColor::Red, false, 5.0f, 0, 5.0f);

    bool bWallHit = GetWorld()->LineTraceSingleByChannel(
        WallHitResult,
        WallTraceStart,
        WallTraceEnd,
        ECC_WorldStatic,
        WallParams
    );

    float DistanceToWall = bWallHit ? (WallHitResult.ImpactPoint - WStartLocation).Size() : 300.0f; 

    float JumpHeightMultiplier = 1.0f;
    float JumpAngle = 45.0f;

   

    if (DistanceToWall < 300.0f){
        float MaxDistance = 300.0f;
        float MoveDistance = FMath::Clamp(MaxDistance - DistanceToWall, 0.0f, MaxDistance);

        FVector AdjustedLocation = WStartLocation - WForwardDirection * MoveDistance;


    
    FVector LaunchVelocity = (AdjustedLocation - WStartLocation).GetSafeNormal() * 600.0f+ MoveDistance; 
    ACharacter* Character = Cast<ACharacter>(Actor);
    if (Character)
        {
            Character->LaunchCharacter(LaunchVelocity, true, true);
            
        }
        return false;
       
        }
    else if (DistanceToWall < 500.0f)
        {
        JumpHeightMultiplier = 70.0f; 
        JumpAngle = 60.0f;
        }

    
    FVector StartLocation = Actor->GetActorLocation();
    FVector ForwardDirection = Actor->GetActorForwardVector();
    FVector EndLocation = StartLocation + ForwardDirection * 500.0f; 


    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Actor);

   
    StartLocation = EndLocation;
    StartLocation.Z += 500.0f;
    EndLocation.Z -= 1000.0f;
    
    //DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5.0f, 0, 5.0f);

    
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_WorldStatic, 
        Params
    );

   
    if (bHit && HitResult.bBlockingHit)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit detected at location: %s"), *HitResult.ImpactPoint.ToString());

        FVector HitLocation = HitResult.ImpactPoint;
        float ZDifference = HitLocation.Z - Actor->GetActorLocation().Z;

        // ZDifference�� ��ȿ�� ��쿡�� ���� ����
        if (ZDifference <= 0)
        {
            // �̵��Ϸ��� ��ǥ ��ġ�� ��� (5000 ���� ��)
            FVector TargetLocation = Actor->GetActorLocation() + ForwardDirection * 300.0f;

            // ��ǥ ���������� ���� �Ÿ��� ���� ���� ���
            float HorizontalDistance = (TargetLocation - Actor->GetActorLocation()).Size2D();
            float HeightDifference = Actor->GetActorLocation().Z - HitLocation.Z;

            // �߷°� ��ǥ �Ÿ� �� �ʱ� �ӵ��� ����Ͽ� �ӵ� ���
            float Gravity = GetWorld()->GetDefaultGravityZ();
            float LaunchSpeed = FMath::Sqrt(-HorizontalDistance * Gravity / FMath::Sin(2 * FMath::DegreesToRadians(45.0f)));

            // X, Y ������ �ӵ� ���
            FVector LaunchVelocity = ForwardDirection * LaunchSpeed;

            // Z ������ �ӵ� ���
            LaunchVelocity.Z = LaunchSpeed * FMath::Sin(FMath::DegreesToRadians(45.0f)) ; 

            // ĳ���Ϳ� ���� ������ ��� ����
            ACharacter* Character = Cast<ACharacter>(Actor);
            if (Character)
            {
                Character->LaunchCharacter(LaunchVelocity, true, true);
                return false;
                UE_LOG(LogTemp, Log, TEXT("Jump Skill applied with LaunchVelocity: %s"), *LaunchVelocity.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to cast Actor to ACharacter"));
            }
        }
        else
        {
            FVector TargetLocation = Actor->GetActorLocation() + ForwardDirection * 500.0f;
            float HorizontalDistance = (TargetLocation - Actor->GetActorLocation()).Size2D();
            float HeightDifference = Actor->GetActorLocation().Z - HitLocation.Z;

            // �߷°� ��ǥ �Ÿ� �� �ʱ� �ӵ��� ����Ͽ� �ӵ� ���
            float Gravity = GetWorld()->GetDefaultGravityZ();
            float LaunchSpeed = FMath::Sqrt(-HorizontalDistance * Gravity / FMath::Sin(2 * FMath::DegreesToRadians(JumpAngle)));

            // X, Y ������ �ӵ� ���
            FVector LaunchVelocity = ForwardDirection * LaunchSpeed;

            // Z ������ �ӵ� ���
            LaunchVelocity.Z = LaunchSpeed * FMath::Sin(FMath::DegreesToRadians(JumpAngle)) + JumpHeightMultiplier;

            ACharacter* Character = Cast<ACharacter>(Actor);
            if (Character)
            {
                Character->LaunchCharacter(LaunchVelocity, true, true);
                return true;
                UE_LOG(LogTemp, Log, TEXT("Jump Skill applied with LaunchVelocity: %s"), *LaunchVelocity.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to cast Actor to ACharacter"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No hit detected or no valid height difference."));
    }
    return false;

}



