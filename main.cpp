#include <Novice.h>
#include "mt.h"

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1 = { 1.2f, -3.9f, 2.5f };
	Vector3 v2 = { 2.8f, 0.4f, -1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraPosition = {0,0,-5.0f};
	Vector3 kLocalVertices[3] = {
		{0.0f, 0.5f, 0.0f,},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f}
	};

	Matrix4x4 worldMatrix = {};
	Matrix4x4 cameraMatrix = {};
	Matrix4x4 viewMatrix = {};
	Matrix4x4 projectionMatrix = {};
	Matrix4x4 worldViewProjectionMatrix = {};
	Matrix4x4 viewportMatrix = {};
	Vector3 ScreenVertices[3] = {};
	Vector3 ndcVertex = {};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
			
		if (keys[DIK_W]) {
			translate.z += 0.1f;
		}
		else if (keys[DIK_S]) {
			translate.z -= 0.1f;
		}
		else if (keys[DIK_A]) {
			translate.x -= 0.1f;
		}
		else if (keys[DIK_D]) {
			translate.x += 0.1f;
		}

		rotate.y += 0.1f;


		worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
		cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		for (uint32_t i = 0; i < 3; ++i) {
			ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			ScreenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, cross, "Cross");
		Novice::DrawTriangle(int(ScreenVertices[0].x), int(ScreenVertices[0].y), int(ScreenVertices[1].x), int(ScreenVertices[1].y), int(ScreenVertices[2].x), int(ScreenVertices[2].y), RED, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
