var CLIENT_ID     = '6e60f3a82663570';
var CLIENT_SECRET = 'bfc21bb2e938ce42c21ac4b19bdfe8947e60ff21';

var AUTH_URL    = 'https://api.imgur.com/oauth2/authorize?client_id=' + CLIENT_ID + '&response_type=code';
var TOKEN_URL   = 'https://api.imgur.com/oauth2/token';
var UPLOAD_URL  = 'https://api.imgur.com/3/image';
var ACCOUNT_URL = 'https://api.imgur.com/3/account/';

var STATS_SUFFIX = '/stats';

var DAY_DURATION = 24 * 60 * 60 * 1000;

function OAuthHeaders(token) {
    return {
        'Content-type'  : 'application/x-www-form-urlencoded',
        'Authorization' : 'Bearer ' + token
    };
}

function codePayload(code) {
    return {
        'code'          : code,
        'grant_type'    : 'authorization_code',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET
    };
}

function refreshPayload(token) {
    return {
        'refresh_token' : token,
        'grant_type'    : 'refresh_token',
        'client_id'     : CLIENT_ID,
        'client_secret' : CLIENT_SECRET
    };
}

function accountInfoUrl(username) {
    return ACCOUNT_URL + username;
}

function accountStatsUrl(username) {
    return accountInfoUrl(username) + STATS_SUFFIX;
}

function daysFrom(date) {
    var now = new Date;

    var dateMs = date.getTime();
    var nowMs  = now.getTime();

    var diff = Math.abs(dateMs - nowMs);
    return Math.round(diff / DAY_DURATION);
}