# haiku-helloworld

`Haiku` の練習空間

## 練習の素材

`Art of Be OS Programming(Japanese)`
https://www.haiku-os.org/legacy-docs/ArtOfBeOSProgramming/


## 書式の統一化

https://www.haiku-os.org/development/coding-guidelines


正直 `Haiku` が推奨するコーディングスタイルは私の好みとは異なるが、できるだけ準拠すべくツールで一括変換することにする。

幸いなことに 書式変換ツールである `astyle`が 移植されており簡単に利用できるのはありがたいことである。

完全ではないが `astylerc_haiku` に詳細なオプションを意図的にロング形式で記述した。
一番良いのは `Haiku`側からオプションファイルを提示してくれることである。

本プロジェクトでは、コミット前に以下のコマンドを実行することにしている。

	astyle --options=astylerc_haiku src/*.cpp src/*.h


執筆中...
