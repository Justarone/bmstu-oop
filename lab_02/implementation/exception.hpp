ExceptionMatrix::ExceptionMatrix(const char *errmsg) {
    int err_len = strlen(errmsg) + 1;
    _errmsg = new char[err_len];
    strncpy(_errmsg, errmsg, err_len - 1);
}

ExceptionMatrix::~ExceptionMatrix() {
    delete []_errmsg;
}

const char *ExceptionMatrix::what() const {
    return _errmsg;
}
