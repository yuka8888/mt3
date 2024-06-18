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

	Sphere sphere{ {0.0f, 0.0f, 0.0f}, 0.5f };
	Plane plane{ {0.0f, -1.0f, 0.0f},{1.0f} };
	uint32_t color = WHITE;

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate = {0.0f, 0.0f, -9.49f };
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

		if (isCollision(sphere, plane)) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		ImGui::DragFloat3("Sphere.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("Sphere.radius", &sphere.radius, 0.01f);
		ImGui::DragFloat("Plane.distance", &plane.distance, 0.01f);
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		plane.normal = Normalize(plane.normal);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, color);
		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);
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
