var CLIENT_ID     = '6e60f3a82663570';
var CLIENT_SECRET = 'bfc21bb2e938ce42c21ac4b19bdfe8947e60ff21';

var REDIRECT_PORT = 1337;

var AUTH_URL       = 'https://api.imgur.com/oauth2/authorize?client_id=' + CLIENT_ID + '&response_type=code';
var TOKEN_URL      = 'https://api.imgur.com/oauth2/token';
var IMAGE_BASE_URL = 'https://api.imgur.com/3/image/'
var UPLOAD_URL     = 'https://api.imgur.com/3/image';
var ACCOUNT_URL    = 'https://api.imgur.com/3/account/';

var STATS_SUFFIX = '/stats';

var IMAGE_IDS_SUFFIX = '/images/ids';
var IMAGE_COUNT_SUFFIX = '/images/count';

var THUMBNAIL_SIZE_SUFFIX = 't' // https://api.imgur.com/models/image

var OAUTH_HEADERS = function(token) {
    return {
        'Content-type'  : 'application/x-www-form-urlencoded',
        'Authorization' : 'Bearer ' + token
    };
};

var CODE_PAYLOAD = function(code) {
    return {
        'code'          : code,
        'grant_type'    : 'authorization_code',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET
    };
};

var REFRESH_PAYLOAD = function(token) {
    return {
        'refresh_token' : token,
        'grant_type'    : 'refresh_token',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET
    };
};

var ACCOUNT_INFO_URL = function(username) {
    return ACCOUNT_URL + username;
};

var ACCOUNT_STATS_URL = function(username) {
    return ACCOUNT_INFO_URL(username) + STATS_SUFFIX;
};

var ACCOUNT_IMAGES_COUNT_URL = function(username) {
    return ACCOUNT_INFO_URL(username) + IMAGE_COUNT_SUFFIX;
}

var ACCOUNT_IMAGES_IDS_URL = function(username, page) {
    var query = {
        'perPage' : '25',
        'page'    : String(page)
    };
    return HTTP.url(ACCOUNT_INFO_URL(username) + IMAGE_IDS_SUFFIX, query);
};

var IMAGE_URL = function(id) {
    return IMAGE_BASE_URL + id
}

var DAY_DURATION = 24 * 60 * 60 * 1000;

function daysFrom(date) {
    var now = new Date;

    var dateMs = date.getTime();
    var nowMs  = now.getTime();

    var diff = Math.abs(dateMs - nowMs);
    return Math.round(diff / DAY_DURATION);
}
