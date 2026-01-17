# Unreal Game Android

Unreal Engine 5 проект для Android платформы с оптимизациями производительности и отображением статистики FPS.

## Особенности

- **Оптимизация производительности**: Настроены параметры рендеринга для мобильных устройств
- **Отображение FPS**: Встроенная система отображения статистики производительности через GameInstance
- **Android поддержка**: Оптимизированные настройки для Android устройств
- **Оптимизация текстур**: Ограниченный пул текстур (400 MB) для лучшей производительности

## Структура проекта

- `Source/Game/` - C++ исходный код игры
- `Content/` - Ассеты Unreal Engine (Blueprints, Meshes, Textures, Animations)
- `Config/` - Конфигурационные файлы (Engine, Scalability, Input)

## Система отображения производительности

Проект включает `PerformanceWidget` и `MyGameInstance` для автоматического отображения статистики:
- FPS (кадров в секунду)
- Frame Time, Game Time, Draw Time, GPU Time, Input Time
- Memory Usage
- Render Resolution
- Draw Calls и Primitives

## Компиляция

1. Откройте `Game.uproject` в Unreal Engine 5
2. Убедитесь, что установлены все зависимости
3. Скомпилируйте проект через IDE (Visual Studio) или через Unreal Engine

## Android сборка

Для сборки на Android используйте стандартный процесс упаковки Unreal Engine:
1. File → Package Project → Android
2. Выберите конфигурацию сборки (ASTC, ETC2 и т.д.)

## Настройки производительности

Основные настройки оптимизации находятся в:
- `Config/DefaultEngine.ini` - настройки движка и рендеринга
- `Config/DefaultScalability.ini` - настройки качества графики

## Автор

aksa4y

## Лицензия

Проект создан для личного использования.
