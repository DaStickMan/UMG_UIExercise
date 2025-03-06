# UMG UI Exercise - Unreal Engine 5

![UIForGameDesigners](https://github.com/user-attachments/assets/2473a532-b4b9-4e8a-9cbf-a1e74232a126)

## Project Overview
A structured implementation of dynamic friend status UI demonstrating MVVM pattern, SOLID principles, and data-driven design in Unreal Engine 5.

## Features

### Core Functionality
- **Dynamic Friend Lists** with online/offline separation
- **Data Table-driven system** using structured friend data:
  ```cpp
  USTRUCT(BlueprintType)
  struct FFriendData {
      GENERATED_BODY()
      UPROPERTY(EditAnywhere) FString Nickname;
      UPROPERTY(EditAnywhere) FDateTime LastOnline;
      UPROPERTY(EditAnywhere) int32 Level;
      UPROPERTY(EditAnywhere) TSoftObjectPtr<UTexture2D> Avatar;
      UPROPERTY(EditAnywhere) bool bIsConnected;
  };
  ```
- **Automatic status simulation** with random 2-5s updates:
  ```cpp
  GetWorld()->GetTimerManager().SetTimer(
      TimerHandle,
      this,
      &UFriendSystem::ChangeStatus,
      FMath::RandRange(2.0f, 5.0f),
      false
  );
  ```
- **Toast notifications** with queue system
- **Animated transitions** for list items and UI elements

## Installation
1. Clone repository:
   ```bash
   git clone https://github.com/DaStickMan/UMG_UIExercise.git
   ```
2. Open in Unreal Engine 5.2+
3. Navigate to `Content/Levels/MainLevel.umap`

## Architecture
```plaintext
View (UMG) ↔ ViewModel (C++) ↔ Service (C++) ↔ Model (Data Assets)
```

### Key Components
| Component | Responsibility |
|-----------|----------------|
| `FriendDataService` | Handles data operations |
| `FriendViewModel` | Mediates layer communication |
| `FriendStatusWidget` | Main UI presentation |

## Development Approach
1. **MVP Implementation**:
   - Core status system
   - Basic list presentation
2. **Iterative Enhancements**:
   - Add animations
   - Implement tooltips
3. **Optimization**:
   - Widget pooling
   - Async loading

## Best Practices
- ✅ Event-driven communication
- ✅ Gray-blocking before polish
- ✅ Widget recycling system
- ✅ Soft references for assets
---
⭐ Star the repository if you find this useful!
