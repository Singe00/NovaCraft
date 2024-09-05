// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSkill.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h" // 디버그용 헤더 추가
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

    // 전방으로 라인 트레이스 (벽과의 거리 측정)
    FVector WallTraceStart = WStartLocation + WForwardDirection * 100.0f; // 캐릭터 앞에서 시작
    FVector WallTraceEnd = WallTraceStart + WForwardDirection * 300.0f; // 300 유닛 앞까지 트레이스

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

    float DistanceToWall = bWallHit ? (WallHitResult.ImpactPoint - WStartLocation).Size() : 300.0f; // 벽까지의 거리

    float JumpHeightMultiplier = 1.0f;
    float JumpAngle = 45.0f;

   

    if (DistanceToWall < 300.0f){
        float MaxDistance = 300.0f; // 최대 이동 거리
        float MoveDistance = FMath::Clamp(MaxDistance - DistanceToWall, 0.0f, MaxDistance);

        FVector AdjustedLocation = WStartLocation - WForwardDirection * MoveDistance;


    // 자연스럽게 이동하도록 LaunchCharacter를 사용
    FVector LaunchVelocity = (AdjustedLocation - WStartLocation).GetSafeNormal() * 600.0f+ MoveDistance; // 속도 조정 가능
    ACharacter* Character = Cast<ACharacter>(Actor);
    if (Character)
        {
            Character->LaunchCharacter(LaunchVelocity, true, true);
            
        }
        return false;
        JumpHeightMultiplier = 80.0f;
        JumpAngle = 60.0f;
        }
    else if (DistanceToWall < 500.0f)
        {
        JumpHeightMultiplier = 70.0f; 
        JumpAngle = 60.0f;
        }

    // 라인 트레이스 시작 지점과 방향 설정
    FVector StartLocation = Actor->GetActorLocation();
    FVector ForwardDirection = Actor->GetActorForwardVector();
    FVector EndLocation = StartLocation + ForwardDirection * 500.0f; // 정면으로 5000 유닛으로 범위 증가

    // 라인 트레이스 설정
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Actor);

    // 라인 트레이스를 위에서 아래로 쏘기 위해서 약간 위로 오프셋
    StartLocation = EndLocation;
    StartLocation.Z += 500.0f;
    EndLocation.Z -= 1000.0f;
    // 디버깅용으로 라인 트레이스를 시각화
    //DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5.0f, 0, 5.0f);

    // 라인 트레이스 수행
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_WorldStatic, // 충돌 채널 설정 (가시성 채널 사용)
        Params
    );

    // 라인 트레이스가 성공한 경우에만 점프 스킬 적용
    if (bHit && HitResult.bBlockingHit)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit detected at location: %s"), *HitResult.ImpactPoint.ToString());

        FVector HitLocation = HitResult.ImpactPoint;
        float ZDifference = HitLocation.Z - Actor->GetActorLocation().Z;

        // ZDifference가 유효한 경우에만 점프 적용
        if (ZDifference <= 0)
        {
            // 이동하려는 목표 위치를 계산 (5000 유닛 앞)
            FVector TargetLocation = Actor->GetActorLocation() + ForwardDirection * 300.0f;

            // 목표 지점까지의 수평 거리와 높이 차이 계산
            float HorizontalDistance = (TargetLocation - Actor->GetActorLocation()).Size2D();
            float HeightDifference = Actor->GetActorLocation().Z - HitLocation.Z; // 높이 차이

            // 중력과 목표 거리 및 초기 속도를 고려하여 속도 계산
            float Gravity = GetWorld()->GetDefaultGravityZ();
            float LaunchSpeed = FMath::Sqrt(-HorizontalDistance * Gravity / FMath::Sin(2 * FMath::DegreesToRadians(45.0f)));

            // X, Y 성분의 속도 계산
            FVector LaunchVelocity = ForwardDirection * LaunchSpeed;

            // Z 성분의 속도 계산
            LaunchVelocity.Z = LaunchSpeed * FMath::Sin(FMath::DegreesToRadians(45.0f)) ; // 45도 각도 기준으로 Z 성분 계산

            // 캐릭터에 대해 포물선 운동을 적용
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

            // 중력과 목표 거리 및 초기 속도를 고려하여 속도 계산
            float Gravity = GetWorld()->GetDefaultGravityZ();
            float LaunchSpeed = FMath::Sqrt(-HorizontalDistance * Gravity / FMath::Sin(2 * FMath::DegreesToRadians(JumpAngle)));

            // X, Y 성분의 속도 계산
            FVector LaunchVelocity = ForwardDirection * LaunchSpeed;

            // Z 성분의 속도 계산
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



