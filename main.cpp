#include <Novice.h>
#include "mt.h"

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = {0.26f, 0.0f, 0.0f};
	Vector3 cameraTranslate = {0.0f, 1.9f, -6.49f};
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

	Sphere sphere = {
		{0.0f, 0.0f, 0.0f},
		0.5f
	};
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

		worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
		cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, BLUE);
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