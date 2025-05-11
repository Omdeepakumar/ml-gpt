<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <meta name="description" content="PDF to Text Converter - Extract accurate content from your PDF files with simple and advanced layout support.">
  <meta name="keywords" content="PDF to Text, PDF Extractor, Layout Preserved, PDF Reader, Online Converter">
  <meta name="author" content="ML Y">
  <title>PDF to Text - Smart Extractor</title>
  <style>
    body {
      margin: 0;
      font-family: "Poppins", sans-serif;
      background-color: #f4f6f9;
      color: #333;
      padding: 30px 20px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }

    h1 {
      font-size: 2rem;
      margin-bottom: 20px;
      background: linear-gradient(to right, #0f62fe, #00b0ff);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .uploader {
      background: white;
      border-radius: 20px;
      padding: 30px;
      box-shadow: 0 8px 25px rgba(0,0,0,0.05);
      text-align: center;
      width: 100%;
      max-width: 500px;
      margin-bottom: 40px;
    }

    .mode-switcher {
      display: flex;
      border: 2px solid #0f62fe;
      border-radius: 12px;
      overflow: hidden;
      margin-bottom: 20px;
    }

    .mode-switcher input[type="radio"] {
      display: none;
    }

    .mode-switcher label {
      flex: 1;
      padding: 10px;
      font-weight: bold;
      text-align: center;
      background: white;
      color: #0f62fe;
      cursor: pointer;
      transition: all 0.3s ease;
    }

    .mode-switcher input[type="radio"]:checked + label {
      background: linear-gradient(to right, #0f62fe, #00b0ff);
      color: white;
    }

    label.upload-btn {
      display: inline-block;
      padding: 12px 20px;
      font-weight: 600;
      color: #0f62fe;
      border: 2px solid #0f62fe;
      border-radius: 10px;
      background: white;
      cursor: pointer;
      transition: all 0.3s ease;
    }

    label.upload-btn:hover {
      background-color: #0f62fe;
      color: white;
    }

    input[type="file"] {
      display: none;
    }

    #loading {
      margin-top: 10px;
    }

    .results {
      width: 100%;
      max-width: 1000px;
      display: flex;
      flex-direction: column;
      gap: 20px;
    }

    .file-output {
      background: white;
      border-left: 5px solid #0f62fe;
      padding: 20px;
      border-radius: 12px;
      box-shadow: 0 4px 20px rgba(0,0,0,0.06);
      position: relative;
    }

    .file-output h3 {
      margin: 0 0 10px 0;
      font-size: 1rem;
      color: #0f62fe;
      word-wrap: break-word;
    }

    .file-output pre {
      font-size: 0.9rem;
      white-space: pre-wrap;
      max-height: 300px;
      overflow-y: auto;
      margin: 0;
    }

    .btn-group {
      display: flex;
      gap: 10px;
      margin: 10px 0;
      flex-wrap: wrap;
    }

    .copy-btn {
      background: linear-gradient(to right, #0f62fe, #00b0ff);
      color: white;
      border: none;
      padding: 8px 16px;
      font-size: 0.8rem;
      border-radius: 8px;
      cursor: pointer;
      transition: 0.3s ease;
    }

    .copy-btn:hover {
      background: #0072ff;
    }

    .copy-btn:active {
      transform: scale(0.95);
    }

    .loader {
      width: 30px;
      height: 30px;
      border: 4px solid rgba(0, 0, 0, 0.1);
      border-top-color: #0f62fe;
      border-radius: 50%;
      animation: spin 0.8s linear infinite;
      margin: 0 auto;
    }

    @keyframes spin {
      to {
        transform: rotate(360deg);
      }
    }

    footer {
      margin-top: 40px;
      text-align: center;
      font-size: 0.9rem;
      color: #666;
    }

    footer div:first-child {
      font-weight: bold;
      font-size: 1.1rem;
      background: linear-gradient(to right, #0f62fe, #00b0ff);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    footer div:last-child {
      margin-top: 5px;
      letter-spacing: 1px;
      font-weight: 600;
      color: #0f62fe;
    }

    @media (max-width: 600px) {
      .file-output {
        padding: 15px;
      }
    }
  </style>
</head>
<body>
  <h1>PDF to Text Converter</h1>

  <div class="uploader">
    <div class="mode-switcher">
      <input type="radio" name="mode" id="simpleMode" value="simple" checked>
      <label for="simpleMode">Simple</label>

      <input type="radio" name="mode" id="advancedMode" value="advanced">
      <label for="advancedMode">Advanced</label>
    </div>

    <label class="upload-btn" for="fileInput">Upload PDF</label>
    <input type="file" id="fileInput" accept="application/pdf" multiple />
    <div id="loading"></div>
  </div>

  <div class="results" id="resultsContainer"></div>

  <footer>
    <div>ML DEVELOPER</div>
    <div>MADE IN INDIA</div>
  </footer>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/pdf.js/3.4.120/pdf.min.js"></script>
  <script>
    const fileInput = document.getElementById("fileInput");
    const resultsContainer = document.getElementById("resultsContainer");
    const loading = document.getElementById("loading");

    function getSelectedMode() {
      return document.querySelector('input[name="mode"]:checked').value;
    }

    function createOutputBox(filename, text) {
      const outputDiv = document.createElement("div");
      outputDiv.classList.add("file-output");

      const heading = document.createElement("h3");
      heading.textContent = filename;

      const btnGroup = document.createElement("div");
      btnGroup.className = "btn-group";

      const copyBtn = document.createElement("button");
      copyBtn.className = "copy-btn";
      copyBtn.textContent = "Copy Text";
      copyBtn.onclick = () => {
        navigator.clipboard.writeText(text);
        copyBtn.textContent = "Copied!";
        setTimeout(() => (copyBtn.textContent = "Copy Text"), 2000);
      };

      const downloadBtn = document.createElement("button");
      downloadBtn.className = "copy-btn";
      downloadBtn.textContent = "Download .txt";
      downloadBtn.onclick = () => {
        const blob = new Blob([text], { type: "text/plain" });
        const link = document.createElement("a");
        link.href = URL.createObjectURL(blob);
        link.download = filename.replace(/\.pdf$/i, ".txt");
        link.click();
      };

      btnGroup.appendChild(copyBtn);
      btnGroup.appendChild(downloadBtn);

      const pre = document.createElement("pre");
      pre.textContent = text;

      outputDiv.appendChild(heading);
      outputDiv.appendChild(btnGroup);
      outputDiv.appendChild(pre);
      resultsContainer.appendChild(outputDiv);
    }

    async function extractText(pdf, mode) {
      let fullText = "";

      for (let i = 1; i <= pdf.numPages; i++) {
        const page = await pdf.getPage(i);
        const content = await page.getTextContent();

        if (mode === "simple") {
          const strings = content.items.map(item => item.str);
          fullText += `\n\n--- Page ${i} ---\n` + strings.join(" ");
        } else {
          const lines = {};
          content.items.forEach(item => {
            const y = Math.floor(item.transform[5]);
            if (!lines[y]) lines[y] = [];
            lines[y].push({x: item.transform[4], str: item.str});
          });

          const sortedLines = Object.keys(lines).sort((a, b) => b - a);
          for (const y of sortedLines) {
            const line = lines[y].sort((a, b) => a.x - b.x).map(i => i.str).join(" ");
            fullText += line + "\n";
          }
        }
      }

      return fullText.trim();
    }

    fileInput.addEventListener("change", async (e) => {
      const files = Array.from(e.target.files);
      if (files.length === 0) return;

      resultsContainer.innerHTML = "";
      loading.innerHTML = '<div class="loader"></div>';

      for (const file of files) {
        const reader = new FileReader();
        reader.onload = async function () {
          const typedArray = new Uint8Array(this.result);
          try {
            const pdf = await pdfjsLib.getDocument(typedArray).promise;
            const text = await extractText(pdf, getSelectedMode());
            createOutputBox(file.name, text);
          } catch (err) {
            alert("Error reading PDF: " + err.message);
          }
          loading.innerHTML = "";
        };
        reader.readAsArrayBuffer(file);
      }
    });
  </script>
</body>
</html>