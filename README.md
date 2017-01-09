# TokushimUniversity_2016_software
This repository contains documents and sources. Used at software training 2016.

## 実行方法
---  
cd <ワーキングディレクトリのパス>/game/src/controller  
make build  
cd <ワーキングディレクトリのパス>/game/bin
* clientサイド: ./game.out C <サーバのIPアドレス>
* serverサイド: ./game.out S <プレイ人数>

## ディレクトリ構成
---  
* docs (ドキュメント保存)
* game (ゲームの素材)
	+ src (ソースファイル保存)
		- controllers (コントローラ)
		- views (ビュー)
		- models (モデル)
		- utils (ライブラリ)
	+ assets (画像データ保存)
	+ bin (コンパイル後の実行ファイル)
