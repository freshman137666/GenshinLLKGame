// Learn more about Tauri commands at https://tauri.app/develop/calling-rust/
use tauri_plugin_shell::ShellExt;


#[tauri::command]
async fn call_my_sidecar(app: tauri::AppHandle) {
  let sidecar_command = app.shell()
    .sidecar("genshen2")
    .unwrap();
  let (mut _rx, mut _child) = sidecar_command.spawn().unwrap();
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_shell::init())
        .invoke_handler(tauri::generate_handler![call_my_sidecar])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
