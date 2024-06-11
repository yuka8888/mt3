#include <Novice.h>
#include "mt.h"
#include <imgui.h>

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Sphere sphere1{ {0.0f, 0.0f, 0.0f}, 0.5f };
	Sphere sphere2{ {0.0f, 0.0f, 1.0f}, 0.3f };

	uint32_t color = WHITE;

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = { 0.5f, 0.0f, 0.0f };
	Vector3 cameraTranslate = {0.0f, 5.9f, -9.49f };
	Vector3 cameraPosition = { 0,0,-5.0f };

	Vector3 start{};
	Vector3 end{};

	Matrix4x4 viewProjectionMatrix = {};
	Matrix4x4 viewportMatrix = {};
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
		viewProjectionMatrix = MakeViewProjectionMatrix({ 1, 1, 1 }, rotate, translate, { 1, 1, 1 }, cameraRotate, cameraTranslate);
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (isCollision(sphere1, sphere2)) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		ImGui::DragFloat3("Sphere1.center", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere1.radius", &sphere1.radius, 0.01f);
		ImGui::DragFloat3("Sphere2.center", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("Sphere2.radius", &sphere2.radius, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, color);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, WHITE);

		DrawGrid(viewProjectionMatrix, viewportMatrix);

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
