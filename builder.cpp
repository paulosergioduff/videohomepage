#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir: " << path << std::endl;
        return "";
    }
    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

void writeFile(const std::string& path, const std::string& content) {
    fs::create_directories(fs::path(path).parent_path());
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Erro ao criar: " << path << std::endl;
        return;
    }
    file << content;
}

int main() {
    const std::string templatePath = "src/templates/player.html";
    const std::string outputPath = "build/index.html";
    const fs::path videoSource = "src/videos/video.mp4";
    const fs::path videoDest = "build/videos/video.mp4";

    // Processar template
    std::string html = readFile(templatePath);
    if (html.empty()) return 1;

    // Substituir placeholder CORRETAMENTE
    const std::string placeholder = "{{VIDEO_PATH}}";
    size_t pos = html.find(placeholder);
    if (pos != std::string::npos) {
        html.replace(pos, placeholder.length(), "videos/video.mp4"); // Tamanho dinâmico
    }

    // Copiar vídeo e criar diretórios
    try {
        fs::create_directories(videoDest.parent_path());
        fs::copy(videoSource, videoDest, fs::copy_options::overwrite_existing);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    // Gerar HTML
    writeFile(outputPath, html);
    std::cout << "Build OK!\n▶ HTML: " << outputPath << "\n▶ Vídeo: " << videoDest << std::endl;
    return 0;
}