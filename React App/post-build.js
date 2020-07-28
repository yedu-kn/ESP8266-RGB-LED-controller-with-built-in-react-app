// Utils to move file to arduino data folder.

const fs = require('fs');

const includedFiles = ['index.html', 'favicon.ico'];

includedFiles.forEach(file => {
  fs.copyFile(
    `build/${file}`,
    `../Arduino/smart-bulb-esp/data/${file}`,
    err => {
      if (err) throw err;
      console.log(`${file}  moved to arduino data folder`);
    }
  );
});
