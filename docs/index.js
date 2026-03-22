const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = process.env.PORT || 3000;

const MIME_TYPES = {
    '.html': 'text/html',
    '.css': 'text/css',
    '.gif': 'image/gif'
};

const server = http.createServer((req, res) => {
    // Si la ruta es /, servimos index.html
    let filePath = req.url === '/' ? 'index.html' : req.url;
    
    // Resolvemos la ruta absoluta del archivo
    let absPath = path.resolve(__dirname, filePath);

    // Verificamos el tipo de contenido
    let ext = path.extname(absPath);
    let contentType = MIME_TYPES[ext] || 'application/octet-stream';

    // Intentamos leer el archivo
    fs.readFile(absPath, (err, data) => {
        if (err) {
            // Error 404: No encontrado
            if (err.code === 'ENOENT') {
                res.writeHead(404, { 'Content-Type': 'text/plain' });
                res.end('404: Archivo no encontrado');
            } else {
                // Error 500: Error del servidor
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end(`500: Error interno del servidor - ${err.code}`);
            }
            return;
        }

        // Si todo está bien, servimos el archivo
        res.writeHead(200, { 'Content-Type': contentType });
        res.end(data);
    });
});

server.listen(PORT, () => {
    console.log(`-----------------------------------------------`);
    console.log(`UvlAuth Landing Page ejecutándose exitosamente.`);
    console.log(`Accede vía: http://localhost:${PORT}`);
    console.log(`-----------------------------------------------`);
});
