function binaryToString(binary) {
  var res = "";
  for (var i = 0; i < binary.length; i = i + 8) {
    res = res + String.fromCharCode(parseInt(binary.substr(i, 8), 2));
  }
  return res;
}
