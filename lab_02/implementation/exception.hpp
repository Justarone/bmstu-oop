ExceptionMatrix::ExceptionMatrix(const string file_info, const int line_info,
                                 const string time_info, const string errmsg) {
    _errmsg = "\nFile: " + file_info + "\nLine: " + line_info + "\nTime: " + time_info + "Message: " + errmsg;
}
