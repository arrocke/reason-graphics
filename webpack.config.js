const path = require('path')

module.exports = {
  entry: './lib/js/src/Main.js',
  output: {
    path: path.resolve(__dirname, './dist'),
    filename: 'bundle.js'
  },
  devtool: 'eval-source-map'
}