#include "StateManager.h"

StateManager::StateManager() {
    freezeMode = false;
    fastMode = false;
    errorCode = ERROR_NONE;
}

void StateManager::setFreeze(bool state) {
    freezeMode = state;
}

void StateManager::setFast(bool state) {
    fastMode = state;
}

void StateManager::setError(ErrorCode code) {
    errorCode = code;
}

bool StateManager::isFreeze() {
    return freezeMode;
}

bool StateManager::isFast() {
    return fastMode;
}

bool StateManager::hasError() {
    return errorCode != ERROR_NONE;
}

ErrorCode StateManager::getError() {
    return errorCode;
}