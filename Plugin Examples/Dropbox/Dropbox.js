// OAuth 2.0
var CLIENT_ID     = 'zw6yixil9jm1r36';
var CLIENT_SECRET = 'a1us9qus51id4rn';
var REDIRECT_PORT = 1337;
var REDIRECT_URI  = 'http:%2f%2flocalhost:' + String(REDIRECT_PORT);

var URL_AUTH      = 'https://www.dropbox.com/1/oauth2/authorize?response_type=code&client_id=' + CLIENT_ID + '&redirect_uri=' + REDIRECT_URI;
var URL_TOKEN     = 'https://api.dropbox.com/1/oauth2/token';

var OAUTH_HEADERS = function(token, noUrlEncode) {
    var headers = {
        'Authorization' : 'Bearer ' + token
    };
    if (!noUrlEncode)
        headers['Content-type'] = 'application/x-www-form-urlencoded';
    return headers;
};

var TOKEN_REQUEST_PAYLOAD = function(code) {
    return {
        'code'          : code,
        'grant_type'    : 'authorization_code',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET,
        'redirect_uri'  : REDIRECT_URI
    };
};

// Plug-in Constants
var IMAGE_FOLDER = 'Images';
var HTML_FOLDER  = 'HTML';
var IMAGE_TYPE   = 'image';
var HTML_TYPE    = 'html';

var THUMBNAIL_PAYLOAD = {
    'size' : 'm'
};

// Endpoints
var URL_FILE_GET        = 'https://api-content.dropbox.com/1/files/sandbox/';
var URL_LINK_PREVIEW    = 'https://api.dropbox.com/1/shares/sandbox/';
var URL_LINK_NO_PREVIEW = 'https://api.dropbox.com/1/media/sandbox/';
var URL_UPLOAD          = 'https://api-content.dropbox.com/1/files_put/sandbox/';
var URL_METADATA_BASE   = 'https://api.dropbox.com/1/metadata/sandbox/';
var URL_SEARCH_BASE     = 'https://api.dropbox.com/1/search/sandbox/';
var URL_THUMBNAIL_BASE  = 'https://api-content.dropbox.com/1/thumbnails/sandbox/';
var URL_DELETE_FILE     = 'https://api.dropbox.com/1/fileops/delete';
var URL_ACCOUNT_INFO    = 'https://api.dropbox.com/1/account/info';
var URL_METADATA_IMAGES = URL_METADATA_BASE + '/' + IMAGE_FOLDER;

var UPLOAD_URL = function(filePath) {
    return URL_UPLOAD + filePath;
};

var LINK_URL = function(withPreview, path) {
    return (withPreview ? URL_LINK_PREVIEW : URL_LINK_NO_PREVIEW) + path;
};

var THUMBNAIL_URL = function(filePath) {
    return URL_THUMBNAIL_BASE + filePath;
};

var GET_FILE_URL = function(filePath) {
    return URL_FILE_GET + filePath;
};

var LINK_PAYLOAD = function(withPreview, shortLink) {
    if (withPreview)
        return {
            'short_url' : shortLink
        };
    else
        return { };
};

var DELETE_FILE_PAYLOAD = function(filePath) {
    return {
        'root' : 'sandbox',
        'path' : filePath
    };
};

// Utilities
var UNITS = ['Bytes', 'KB', 'MB', 'GB', 'TB'];

function bytesToHumanReadable(bytes) {
    var bits = Math.floor(Math.log(bytes) / Math.log(2));
    bits = Math.max(0, bits);

    var i = Math.floor(bits / 10);
    bytes = bytes / Math.pow(2, 10 * i);

    return bytes.toFixed(2) + ' ' + UNITS[i];
}

String.prototype.startsWith = function(str) {
    return this.slice(0, str.length) == str;
};
