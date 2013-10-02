// OAuth 2.0
var CLIENT_ID     = 'zw6yixil9jm1r36';
var CLIENT_SECRET = 'a1us9qus51id4rn';
var REDIRECT_PORT = 1337;
var REDIRECT_URI  = 'http:%2f%2flocalhost:' + String(REDIRECT_PORT);

var URL_AUTH      = 'https://www.dropbox.com/1/oauth2/authorize?response_type=code&client_id=' + CLIENT_ID + '&redirect_uri=' + REDIRECT_URI;
var URL_TOKEN     = 'https://api.dropbox.com/1/oauth2/token';

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

// Endpoints
var API_BASE_DOMAIN    = 'api';
var API_CONTENT_DOMAIN = 'api-content';
var API_ROOT           = 'sandbox';
var API_URL_BASE       = function(endpoint, contentDomain) {
    var domain = contentDomain ? API_CONTENT_DOMAIN : API_BASE_DOMAIN;
    return 'https://' + domain + '.dropbox.com/1/' + endpoint + '/' + API_ROOT + '/';
};

var URL_FILE_GET        = API_URL_BASE('files', true);
var URL_LINK_PREVIEW    = API_URL_BASE('shares');
var URL_LINK_NO_PREVIEW = API_URL_BASE('media');
var URL_UPLOAD          = API_URL_BASE('files_put', true);
var URL_METADATA_BASE   = API_URL_BASE('metadata');
var URL_SEARCH_BASE     = API_URL_BASE('search');
var URL_THUMBNAIL_BASE  = API_URL_BASE('thumbnails', true);

var URL_DELETE_FILE     = 'https://api.dropbox.com/1/fileops/delete';

var URL_ACCOUNT_INFO    = 'https://api.dropbox.com/1/account/info';

function linkUrl(withPreview) {
    return withPreview ? URL_LINK_PREVIEW : URL_LINK_NO_PREVIEW;
}

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