# haiku-helloworld

`Haiku`プログラミングの練習空間

## 練習の素材

=> [Art of BeOS Programming(Japanese)](https://www.haiku-os.org/legacy-docs/ArtOfBeOSProgramming/)

## 素材に対する変更点

これは、原版に対する批判ではない。当時と事情が異なるという意味で適宜読み替えて参考にするべきものである。

* [x] コンパイラーフラグはc++17
* [x] `NULL` ではなく `nullptr`
* [x] `Draw(BRect update)`ではなく`Invalidate(BRect updateRect)`または`Invalidate()`
* [x] `<interface/Window.h>` ではな `<Window.h>`
* [ ] `BList`ではなく`BObjectList`
* [ ] new ではなく uniqe_ptr, shared_ptrがまともに使えるか検証
* [ ] STLの採用

STLは便利かもしれないが 
* std:: などダブルコロンを多用し視認性が劣る。
* コードサイズが肥大化する。
Haikuには似合わない感がある。（とはいえ、既にサンプルコード内で採用されている）


## 推奨される開発方法との相違

* [`jam`](https://www.perforce.com/documentation/jam-documentation) ベースではなく `CMake`
* [`haiku-format`](https://github.com/owenca/haiku-format) ではなく [`astyle`](http://astyle.sourceforge.net/)
* [`Paladin`](https://github.com/adamfowleruk/Paladin) + [`Koder`](https://github.com/KapiX/Koder) ではなく `emacs`

否定ではなく、ニワカなため試していないだけ。

なかなか慣れた環境からの移行は難しいのだが、Paladin + Koder でコード補完ができるのであれば使ってみたい。

## 開発環境の整備

* [ ] ccls
* [ ] emacs
    * [ ] campany with ccls
    * [ ] campany-lsp clangd (まだ設定不足)


## 書式の統一化

=> [Coding Guidelines](https://www.haiku-os.org/development/coding-guidelines)


正直 `Haiku` が推奨するコーディングスタイルは私の好みとは異なるが、できるだけ準拠すべくツールで一括変換することにする。

幸いなことに 書式変換ツールである `astyle`が 移植されており簡単に利用できるのはありがたいことである。(haiku-formatは導入が面倒なので現時点では見送る)

完全ではないが `astylerc_haiku` に詳細なオプションを意図的にロング形式で記述した。
一番良いのは `Haiku`側からオプションファイルを提示してくれることである。

本プロジェクトでは、コミット前に以下のコマンドを実行することにしている。

```
astyle --options=astylerc_haiku src/*.cpp src/*.h
```

## github 上でのコードの閲覧

Haiku はハードタブを推奨するため、ブラウザの標準タブ幅である8によりガタガタに表示される。

回避策として

[タブ幅4の閲覧](./Tab4Links.md)を参照

# VSCodeの設定(Linux)

## c_cpp_properties.json

HaikuのターミナルでincludePath部分を生成しておく

```
ruby -e 'p ENV["BEINCLUDES"].split(/;/).map { |each|
	"${haiku_repo}/" +  each.gsub("/boot/system/develop/", "")
	.gsub("headers/be", "headers/os") 
}'
```

あとは、

```
"env": { 
	"haiku_repo": "<path to haiku repository">, 
	... 
},
...
```


