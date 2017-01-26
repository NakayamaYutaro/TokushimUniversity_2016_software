/*************************************************
コンパイルオプション：-lSDL -lSDL_gfx -lcwiimote -D_ENABLE_TILT -D_ENABLE_FORCE -L/usr/lib
備考：座標最小最大値・・・x:[0:1791] y:[0:1272]
*************************************************/

#include <stdio.h>
#include <libcwiimote/wiimote.h>	// Wiiリモコンを用いるために必要なヘッダファイル
#include <libcwiimote/wiimote_api.h>	// Wiiリモコンを用いるために必要なヘッダファイル

#define FIELD_WIDTH 3000
#define FIELD_HEIGHT 800

/*
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 800
*/

#define POINT_X_MIN 0
#define POINT_X_MAX 1791
#define POINT_Y_MIN 0
#define POINT_Y_MAX 1272

void map2Field(int x1, int y1, int* x2, int* y2) {
	*x2 = x1 * FIELD_WIDTH / (POINT_X_MAX - POINT_X_MIN);
	*y2 = y1 * FIELD_HEIGHT / (POINT_Y_MAX - POINT_Y_MIN);
}

// メイン関数
int main(int argc, char* argv[]) {
	// Wiiリモコンを用いるための構造体を宣言（初期化）
	wiimote_t wiimote = WIIMOTE_INIT;	// Wiiリモコンの状態格納用
	wiimote_report_t report = WIIMOTE_REPORT_INIT;	// レポートタイプ用

	// ***** Wiiリモコン処理 *****
	if(argc < 2) {	// Wiiリモコン識別情報がコマンド引数で与えられなければ
		printf("Designate the wiimote ID to the application.\n");
		exit(1);
	}

	// Wiiリモコンの接続（１つのみ）
	if(wiimote_connect(&wiimote, argv[1]) < 0) {	// コマンド引数に指定したWiiリモコン識別情報を渡して接続
		printf("unable to open wiimote: %s\n", wiimote_get_error());
		exit(1);
	}

	wiimote.led.one  = 1;	// WiiリモコンのLEDの一番左を点灯させる（接続を知らせるために）
	//wiimote.led.four  = 1;	// WiiリモコンのLEDの一番右を点灯させる

	// Wiiリモコンスピーカの初期化
	//wiimote_speaker_init(&wiimote, WIIMOTE_FMT_S4, WIIMOTE_FREQ_44800HZ);

        // センサからのデータを受け付けるモードに変更
        wiimote.mode.acc = 1;
	wiimote.mode.ir = 1;

	// Wiiリモコンがオープン（接続状態）であればループ
	while(wiimote_is_open(&wiimote)) {
		// Wiiリモコンの状態を取得・更新する
		if(wiimote_update(&wiimote) < 0) {
			wiimote_disconnect(&wiimote);
			break;
		}

		// ***** Wiiのキー（ボタン）ごとに処理 *****
		// HOMEボタンが押された時
		if(wiimote.keys.home) {
			wiimote_speaker_free(&wiimote);	// Wiiリモコンのスピーカを解放
			wiimote_disconnect(&wiimote);	// Wiiリモコンとの接続を解除
		}

                if(1) {
			// ***** Wiiリモコンの状態を表示 *****
			printf("MODE %02x\n", wiimote.mode.bits);	// モード
			printf("BAT %02x\n", wiimote.battery);	// バッテリ残量
                    
			// ボタンの状態
			printf("KEYS %04x one=%d two=%d a=%d b=%d <=%d >=%d ^=%d v=%d h=%d +=%d -=%d\n",
				wiimote.keys.bits, 
				wiimote.keys.one,
				wiimote.keys.two,
				wiimote.keys.a,
				wiimote.keys.b,
				wiimote.keys.left,
				wiimote.keys.right,
				wiimote.keys.up,
				wiimote.keys.down,
				wiimote.keys.home,
				wiimote.keys.plus,
				wiimote.keys.minus);
                  
			// 赤外線センサの状態（ポインティングの座標等）
			printf("IR1 x=%04d y=%04d ss=%d\n",
				wiimote.ir1.x,
				wiimote.ir1.y,
				wiimote.ir1.size);
		}
	}
	return 0;
}
