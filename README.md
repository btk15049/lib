# ライブラリ置き場

## Visual Studio Code でのテストの実行方法

### 拡張機能

- CMake
- CMake Tools
- CMake Tools Helper
- cmake-format

### settings.json

ビルド時のコマンドを環境変数で設定しているので`settings.json`の`settings`の項にパスを書く

```json
    "cmake.environment": {
      "BUILD_CMD": "$(which g++)",
      "LIB_PATH": "${REPOSITORY_ROOT}/lib/src",
      "BOOST_PATH": "boostのパス(例：/usr/local/Cellar/boost/1.68.0/include)"
    }
```
