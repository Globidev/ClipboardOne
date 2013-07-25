var CLIENT_ID     = 'zw6yixil9jm1r36';
var CLIENT_SECRET = 'a1us9qus51id4rn';
var REDIRECT_URI  = 'http:%2f%2flocalhost:1337';

var AUTH_URL            = 'https://www.dropbox.com/1/oauth2/authorize?response_type=code&client_id=' + CLIENT_ID + '&redirect_uri=' + REDIRECT_URI;
var TOKEN_URL           = 'https://api.dropbox.com/1/oauth2/token';
var LINK_URL_PREVIEW    = 'https://api.dropbox.com/1/shares/sandbox/Images/';
var LINK_URL_NO_PREVIEW = 'https://api.dropbox.com/1/media/sandbox/Images/';
var UPLOAD_URL          = 'https://api-content.dropbox.com/1/files_put/sandbox/Images/';
var ACCOUNT_INFO_URL    = 'https://api.dropbox.com/1/account/info';

var UNITS = ['Bytes', 'KB', 'MB', 'GB', 'TB'];

function OAuthHeaders(token) {
    return {
        'Content-type'  : 'application/x-www-form-urlencoded',
        'Authorization' : 'Bearer ' + token
    };
}

function tokenRequestParameters(code) {
    return {
        'code'          : code,
        'grant_type'    : 'authorization_code',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET,
        'redirect_uri'  : REDIRECT_URI
    };
}

function linkUrl(withPreview) {
    return withPreview ? LINK_URL_PREVIEW : LINK_URL_NO_PREVIEW;
}

function bytesToHumanReadable(bytes) {
    var bits = Math.floor(Math.log(bytes) / Math.log(2));
    bits = Math.max(0, bits);

    var i = Math.floor(bits / 10);
    bytes = bytes / Math.pow(2, 10 * i);

    return bytes.toFixed(2) + ' ' + UNITS[i];
}