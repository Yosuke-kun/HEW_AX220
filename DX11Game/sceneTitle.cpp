//===================================================
//		タイトルシーン[sceneTitle.cpp]
//小楠裕子
//2021/11/30	ファイル作成
//=====================================================
#include "sceneTitle.h"
#include "fade.h"
#include "bg.h"
#include "input.h"


//*****グローバル変数*****
static BG* g_pBG;		//背景

//=============================
//		初期化
//=============================
HRESULT InitSceneTitle() {
	HRESULT hr = MB_OK;


	// 背景初期化
	g_pBG = new BG;



	return hr;
}

//=============================
//		終了
//=============================
void UninitSceneTitle() {
	
	// 背景終了処理
	delete g_pBG;

	
}

//=============================
//		更新
//=============================
void UpdateSceneTitle() {
	

	// 背景更新
	g_pBG->Update();


	/*if (GetKeyPress(VK_F1)) {
		StartFadeOut(SCENE_SAMPLE);
	}*/
	if (GetKeyPress(VK_F2)) {
		StartFadeOut(SCENE_GAME);
	}

	if (GetKeyPress(VK_RETURN))
	{
		StartFadeOut(SCENE_MAP);

	}

	
}

//=============================
//		描画
//=============================
void DrawSceneTitle() {
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 背景描画
	g_pBG->Draw();


	
}