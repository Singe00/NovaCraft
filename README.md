# Project NovaCraft
<br/>
![image](https://github.com/user-attachments/assets/fc223ac4-aa09-41b7-bcff-6bc448628008)


[NovaCraft 플레이영상](https://tv.kakao.com/v/449866071)

## 프로젝트 소개
GCC 사관학교 팀프로젝트로 진행되는 프로젝트입니다.

멀티플레이 RTS 장르 게임을 개발합니다.

- 게임명 : NovaCraft
- 장르 : RTS(Real-Time Strategy)
- 플랫폼 : Windows Desktop
- 개발 인원 : 5인
- 개발 기간 : 2024.06.25(화) ~ 2024.09.30(월) 예상

<br/>

## 팀원 구성

### Team
|<img src="https://avatars.githubusercontent.com/u/103260185?v=4" width="150" height="150"/>|<img src="https://avatars.githubusercontent.com/u/110752012?v=4" width="150" height="150"/>|<img src="https://avatars.githubusercontent.com/u/173750469?v=4" width="150" height="150"/>|<img src="https://avatars.githubusercontent.com/u/95664246?v=4" width="150" height="150"/>|
|:-:|:-:|:-:|:-:|
|조시완<br/>[@Singe00](https://github.com/Singe00)|백재현<br/>[@bbaekjae](https://github.com/bbaekjae)|정호용<br/>[@TR99990](https://github.com/TR99990)|백민성<br/>[@minmonth](https://github.com/minmonth)|

### 역할 분담
- 조시완 : 팀장, Git 관리, Client Develope (베이스 클래스 설계 및 구축, 플레이어 컨트롤 시스템 개발)
- 백재현 : 부팀장, Client Develope (단축키 컨트롤 시스템 연동 및 개발)
- 백민성 : Client Develope (인게임 시스템 개발 - Grid 시스템, 전장의 안개)
- 정호용 : Client Develope (건물 빌딩 시스템, 유닛 생성 및 업그레이드 시스템 개발)
- 강동우 : 게임 기획 (게임 기획 및 레벨 디자인 설계)
- 공통   : 유닛 설계 및 개발, 레벨 디자인

<br/>

## 플레이 영상
『[플레이 영상](https://www.youtube.com/watch?v=cGzZhg2UonM&t=114s)』

<br/>

## 개발 환경
- Windows 11 (64bits)
- Unreal Engine 5.4.2
- Visual Studio 2022
- Git
- GitHub
 
<br/>

## 개발 기술 및 브랜치 전략

> 개발
  <p>Blueprint 개발  : 로직, 사운드, 이펙트, 애니메이션 상세 작업 진행</p>
  
  <p>C++ 개발   : 베이스 클래스 및 Enum, Structure 구현</p>
  <br/>
  
> 브랜치 전략
- 개인 개발 브랜치 생성
- 개인 작업 디렉토리 내에서만 수정
- 주간 팀 회의 시 작업 보고 및 코드 리뷰 후 병합

  <br/>
  
<br/>

## 프로젝트 구조

## 베이스 클래스 설계
![NovaCraft_Diagram](https://github.com/Singe00/NovaCraft/assets/103260185/ac830a1a-b793-432f-97ee-14fcb4ac7025)


## 개발 기간 및 작업 관리

### 간트차트 확인
- 『[NovaCraft Gantt.xlsx](https://github.com/user-attachments/files/16118383/NovaCraft.Gantt.xlsx)』 파일 참조

## 기록

#### 1. 팀명 및 게임 기획 회의✔
- 회의 날짜/시간 : 2023.06.25(화) / 10:00 ~ 13:00
- 회의 내용 : 팀명 선정 및 게임 기획 및 방향성 선정
- 회의 결론 : Team. NOVA로 팀명 선정, RTS장르의 게임 개발 방향성 확정
- 자세한 내용은 repository에 첨부된 『[기본 게임 설계 회의록](https://www.canva.com/design/DAGJGJLHwQY/e_ffbiNSFZW-HYwsCijtOA/view?utm_content=DAGJGJLHwQY&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 2. 인게임 개발 파트 설계✔
- 회의 날짜/시간 : 2023.06.30(일) / 18:00 ~ 19:30
- 회의 내용 : 게임 플레이에 필요한 구현 내용 및 개발 파트를 설계
- 회의 결론 : 인게임, 유닛, 건물, UI 등의 기능과 상세 내용을 정리
- 자세한 내용은 repository에 첨부된 『[인게임 개발 파트 설계](https://www.canva.com/design/DAGJm21AxXk/zGuZKcOxCjTdh1tVZLZ6Ig/view?utm_content=DAGJm21AxXk&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 3. 개발 파트 분배 회의✔
- 회의 날짜/시간 : 2023.07.08(월) / 09:30 ~ 10:30
- 회의 내용 : 팀 프로젝트 개발 파트를 분배 및 조정
- 회의 결론 : 회의록 참고
- 자세한 내용은 repository에 첨부된 『[개발 파트 분배](https://www.canva.com/design/DAGKpFelIzg/ClH2v5dzNfUCWBaH9dpu3A/view?utm_content=DAGKpFelIzg&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 4. 개발 시퀀스 설계 회의✔
- 회의 날짜/시간 : 2023.07.11(목) / 17:30 ~ 18:00
- 회의 내용 : 프로젝트 개발 사항 구현 계획 및 설계
- 회의 결론 : 각 파트 별 시퀀스 정리 및 필요한 이벤트 요청
- 자세한 내용은 repository에 첨부된 『[개발 시퀀스 설계 회의](https://www.canva.com/design/DAGKpGPWGtg/SzXDJxRqB458DHdE_MLMFg/view?utm_content=DAGKpGPWGtg&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 5. 세계관 및 유닛 디자인 회의✔
- 회의 날짜/시간 : 2023.07.19(금) / 14:00 ~ 17:00
- 회의 내용 : 게임 세계관 및 유닛 상세 기획 회의
- 회의 결론 : 종족 컨셉 결정 및 유닛 상세 기획, 디자인, 패턴 회의 완료
- 자세한 내용은 repository에 첨부된 『[기획 및 유닛 상세 디자인 회의](https://www.canva.com/design/DAGLZB1rNGY/VTtA8wVs6jg6cQdEmuA-3Q/view?utm_content=DAGLZB1rNGY&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 6. 건물 상세 디자인 회의 및 피드백✔
- 회의 날짜/시간 : 2023.08.02(금) / 09:00 ~ 11:00
- 회의 내용 : 건물 상세 디자인 및 개발 코드 리뷰 피드백
- 회의 결론 : 건물 소환 방법, 종류 및 추가 미구현 사항 추합
- 자세한 내용은 repository에 첨부된 『[건물 상세 디자인 회의 및 피드백](https://www.canva.com/design/DAGMqGRCEnQ/w0Viho3S-Ryf5wvmtIGbJA/view?utm_content=DAGMqGRCEnQ&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 7. 중간 발표 전 개발 회의✔
- 회의 날짜/시간 : 2023.08.14(수) / 09:00 ~ 11:30
- 회의 내용 : 개발 진행 상황 보고 및 계획 수립
- 회의 결론 : 중간 발표 전 최소 개발 완료 사항 확정
- 자세한 내용은 repository에 첨부된 『[중간 발표 전 개발 회의](https://www.canva.com/design/DAGOQBBta1M/4hs_cRmlEOOaoxbB6uo7Hg/view?utm_content=DAGOQBBta1M&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 8. 중간 발표 후 개발 작업 회의✔
- 회의 날짜/시간 : 2023.08.26(월) / 14:00 ~ 17:00
- 회의 내용 : 중간 발표 후 개발 계획 수립
- 회의 결론 : 각 파트 별 세부 미관 작업 집중
- 자세한 내용은 repository에 첨부된 『[중간 발표 후 개발 작업 회의](https://www.canva.com/design/DAGPkN1Thyo/aUvmBJ9B_iaGgm84Vo0Dkw/view?utm_content=DAGPkN1Thyo&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

#### 9. 개발 진행 상황 보고 및 연휴 개발 계획 수립 회의✔
- 회의 날짜/시간 : 2023.09.06(금) / 15:00 ~ 18:00
- 회의 내용 : 현재 개발 이슈 및 연휴 개발 계획 수립
- 회의 결론 : 23일까지 기능 개발 종료 후 개발 내용 검토 및 최적화
- 자세한 내용은 repository에 첨부된 『[개발 진행 상황 보고 및 연휴 개발 계획 수립 회의](https://www.canva.com/design/DAGP9m9tYqE/ZC5XtbX49I5NnypUZJpkpA/view?utm_content=DAGP9m9tYqE&utm_campaign=designshare&utm_medium=link&utm_source=editor)』 파일 참조

## 이슈
- 2024.06.25(화)<br/>
  언리얼 프로젝트, Github, Git 연동 완료<br/>

- 2024.08.26(월)<br/>
  프로젝트 Steam 등록 준비 완료<br/>


## 에셋

### 모델링
#### 구매
- 『[CSC 로봇 에셋](https://www.unrealengine.com/id/login/api/login?client_id=43e2dea89b054198a703f6199bee6d5b&redirect_uri=https%3A%2F%2Fwww.unrealengine.com%2Fmarketplace%2Fen-US%2Fproduct%2Fcombat-systems-constructor%3FsessionInvalidated%3Dtrue&prompt=pass_through)』구매
- 『[Sci-FI Troopers Collection](https://www.unrealengine.com/id/login/api/login?client_id=43e2dea89b054198a703f6199bee6d5b&redirect_uri=https%3A%2F%2Fwww.unrealengine.com%2Fmarketplace%2Fko%2Fproduct%2Fsci-fi-troopers-collection%3Fnamespace%3Due%26offers%3D9601dac9f256456796716b70bf84725b%26orderId%3DA2407260115355633%26purchaseToken%3D4823c63c1ff644b9ba802b8c3dd3e6de%26highlightColor%3D0074E4%26sessionInvalidated%3Dtrue&prompt=pass_through)』구매
- 『[SCI FI CREATURES PACK VOL 1](https://www.unrealengine.com/marketplace/ko/product/sci-fi-creatures-pack-vol)』구매
- 『[SCI-FI SNIPER RIFLE - RAILGUN](https://www.unrealengine.com/marketplace/ko/product/sci-fi-sniper-rifle-railgun)』구매
- 『[Sci-fi Arsenal Vol 2.0](https://www.unrealengine.com/marketplace/ko/product/sci-fi-arsenal-vol-2)』구매
- 『[Sci-Fi Machine Gun](https://www.unrealengine.com/marketplace/ko/product/sci-fi-machine-gun)』구매
- 『[SciFi Rocket Launcher AK9 Playable](https://www.unrealengine.com/marketplace/ko/product/scifi-rocket-launcher-ak9?sessionInvalidated=true)』구매
- 『[]()』구매
- 『[]()』구매

#### 무료
- 『[Paragon Wraith](https://www.unrealengine.com/id/login/api/login?client_id=43e2dea89b054198a703f6199bee6d5b&redirect_uri=https%3A%2F%2Fwww.unrealengine.com%2Fmarketplace%2Fen-US%2Fproduct%2Fcombat-systems-constructor%3FsessionInvalidated%3Dtrue&prompt=pass_through)』사용
- 『[AJF-12 "Dvergr"](https://sketchfab.com/3d-models/ajf-12-dvergr-ecc16e103e79448faf9730f172a1d7e8)』사용
- 『[TIE Runner](https://sketchfab.com/3d-models/tie-runner-b209951dbdff45a297fcf212f0fc6bd7)』사용
- 『[SpaceShip](https://sketchfab.com/3d-models/spaceship-6164a883f57f4f13938c3c5999bc0e1f)』사용


### 이미지
#### 무료
- 『[Flaticon](https://www.flaticon.com/)』
- 『[CheckBox Free Image](https://www.flaticon.com/authors/google-material-design/monochrome?author_id=55&type=standard)』사용


### 사운드
#### 구매
#### 무료
- 『[Wind](https://pixabay.com/ko/sound-effects/wind-47344/)』사용

  
### 기타
#### 구매
- 『[Pro Main Menu V3](https://www.unrealengine.com/marketplace/ko/product/pro-main-menu-pack)』
- 『[Grid-Based Builder](https://www.unrealengine.com/marketplace/ko/product/grid-based-builder)』구매

#### 무료
