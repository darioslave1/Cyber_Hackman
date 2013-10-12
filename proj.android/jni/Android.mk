LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AIEffect.cpp\
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/BluEnemy.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/EnemyPathfindingState.cpp \
				   ../../Classes/EnemyPatrolState.cpp \
				   ../../Classes/Entity.cpp \
				   ../../Classes/EntityManager.cpp \
				   ../../Classes/GameLevel.cpp \
				   ../../Classes/GameLevelMap.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/IntroScene.cpp \
				   ../../Classes/MovingEntity.cpp \
				   ../../Classes/PathPlanner.cpp \
				   ../../Classes/Player.cpp \
				   ../../Classes/PlayerNormalState.cpp \
				   ../../Classes/RedEnemy.cpp \
				   ../../Classes/State.h \
				   ../../Classes/StateMachine.h \
				   ../../Classes/WinnerScene.cpp \
				   ../../Classes/HelloWorldScene.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
