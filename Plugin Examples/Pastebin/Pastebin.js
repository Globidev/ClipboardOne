var API_KEY = '857aa0416a7d7a1b5666292b9e9c560c';

var API_URL = 'http://pastebin.com/api/api_post.php';

function pastePayload(text) {
    return {
        'api_dev_key'    : API_KEY,
        'api_option'     : 'paste',
        'api_paste_code' : text
    }
}
