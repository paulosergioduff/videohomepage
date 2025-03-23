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
    
    // Novas linhas adicionadas
    const fs::path styleSource = "src/templates/style.css";
    const fs::path styleDest = "build/lib/style.css";
    const fs::path jsSource = "src/templates/video.js";
    const fs::path jsDest = "build/lib/video.js";

    // Processar template
    std::string html = readFile(templatePath);
    if (html.empty()) return 1;

    // Substituir placeholder
    const std::string placeholder = "{{VIDEO_PATH}}";
    size_t pos = html.find(placeholder);
    if (pos != std::string::npos) {
        html.replace(pos, placeholder.length(), "videos/video.mp4");
    }

    // Copiar vídeo
    try {
        fs::create_directories(videoDest.parent_path());
        fs::copy(videoSource, videoDest, fs::copy_options::overwrite_existing);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    // Bloco novo para copiar CSS/JS
    try {
        // Criar diretório lib
        fs::create_directories(styleDest.parent_path());
        
        // Copiar CSS
        std::string cssContent = readFile(styleSource.string());
        writeFile(styleDest.string(), cssContent);
        
        // Copiar JS
        std::string jsContent = readFile(jsSource.string());
        writeFile(jsDest.string(), jsContent);
        
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erro ao copiar recursos: " << e.what() << std::endl;
        return 1;
    }

    // Gerar HTML
    writeFile(outputPath, html);
    std::cout << "Build OK!\n▶ HTML: " << outputPath 
              << "\n▶ Vídeo: " << videoDest
              << "\n▶ CSS: " << styleDest
              << "\n▶ JS: " << jsDest << std::endl;
    return 0;
}