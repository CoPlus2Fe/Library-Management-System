# Library-Management-System 项目文档

## 项目简介
- 名称：Library-Management-System
- 描述：基于协同过滤（Collaborative Filtering）的图书馆借阅管理与推荐系统。提供图书管理、读者管理、借阅管理、借阅排行榜以及基于历史交互的图书推荐功能。

## 仓库结构（摘要）
- backend/: 后端 C++ 实现，包含主要逻辑和数据文件。
  - main.cpp: 程序入口与主菜单。
  - bookManager.cpp / bookManager.h: 图书管理相关实现。
  - readerManager.cpp / readerManager.h: 读者管理。
  - borrowManager.cpp / borrowManager.h: 借阅/归还逻辑。
  - dataLoader.cpp / dataLoader.h: 数据加载/保存工具。
  - utils.cpp / utils.h: 通用工具函数（文件检查、辅助操作等）。
  - rank.cpp / rank.h: 借阅排行榜生成功能。
  - cf/: 协同过滤相关实现（`recommender.cpp`, `recommender.h`）。
  - data/: 额外数据（`inter_reevaluation.csv`, `user.csv`, `item.csv`）。
  - item1.csv, records.csv, user.csv: 运行所需的 CSV 数据文件（位于 backend/ 根或 data/ 中，见 `config.h`）。
- frontend/: （当前为空或前端资源/占位）。

## 关键配置
- 路径配置位于 `backend/config.h`，默认常量：
  - `BOOKS_PATH = "item1.csv"`
  - `READERS_PATH = "user.csv"`
  - `RECORDS_PATH = "records.csv"`
  - `DATA_FOLDER = "data"`

请根据实际运行目录调整这些路径（默认假定在 `backend/` 下运行可直接访问这些文件）。

## 构建与运行（快速指南）
1. 进入后端目录：

```bash
cd backend
```

2. 使用 g++ 编译（示例，适用于 macOS/Linux）：

```bash
g++ -std=c++11 -O2 -o lms main.cpp bookManager.cpp readerManager.cpp borrowManager.cpp dataLoader.cpp rank.cpp utils.cpp cf/recommender.cpp -I.
```

3. 运行可执行文件：

```bash
./lms
```

说明：如果增加/修改了源文件，请在编译命令中添加对应的 `.cpp` 文件。若使用 IDE（如 CLion、Xcode），可直接导入 `backend` 目录并创建相应的运行配置。

## 模块说明（摘要）
- `main.cpp`：程序入口，提供文本菜单交互，负责初始化文件与数据文件夹并驱动各管理器模块。
- `bookManager`：支持新增、查询、展示图书等操作，底层读写 `BOOKS_PATH`。
- `readerManager`：管理读者信息，底层读写 `READERS_PATH`。
- `borrowManager`：处理借阅与归还，记录写入 `RECORDS_PATH`，并与 `bookManager`、`readerManager` 协同工作。
- `dataLoader` / `dataStructs.h`：定义数据结构与 CSV 读写逻辑。
- `rank`：统计并生成借阅排行榜（Top10 等）。
- `cf/recommender.cpp`：基于协同过滤实现推荐逻辑，使用历史交互或评分数据生成推荐。

## 数据文件说明
- `item1.csv`：图书项目信息（ID、名称、作者等）。
- `user.csv`：读者/用户信息。
- `records.csv`：借阅记录（用于排行与推荐）。
- `backend/data/`：包含数据集（如 `inter_reevaluation.csv`、`item.csv`、`user.csv`），可用于更复杂的推荐实验或导入。

在首次运行时，程序会尝试创建缺失的文件与目录（见 `utils.cpp` 的辅助函数）。

## 推荐系统（协同过滤）说明
- 推荐实现位于 `backend/cf/recommender.cpp`，核心职责：
  - 根据用户-图书交互矩阵计算相似度（用户或物品层面），
  - 为指定用户生成候选图书并排序返回。

如需替换/扩展推荐算法，可在 `cf/` 目录中修改或增加新策略，保持接口兼容以便在主程序中调用。

## 常见操作与扩展建议
- 添加新字段（如图书类别、借阅次数）时，需同时更新 `dataStructs.h`、CSV 读写逻辑与对应模块的展示/查询函数。
- 若在 Windows/macOS/Linux 间移植，请注意 `system("cls")` / `system("clear")` 清屏差异（`main.cpp` 当前混用 Windows 的 `cls`）。
- 若并发访问或多人使用，建议后续引入轻量数据库（SQLite）替代 CSV 文件以避免一致性问题。
