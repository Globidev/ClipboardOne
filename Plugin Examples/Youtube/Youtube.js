.import "urllib.js" as Urllib

var YOUTUBE_DOMAIN = 'youtube.com';
var YOUTU_BE_DOMAIN = 'youtu.be';
var QUERY_VIDEO_KEY = 'v';
var QUERY_PLAYLIST_KEY ='list';

function isVideo(url) {
    var parsedUrl = Urllib.URL(url);
    if (parsedUrl.domain() === YOUTU_BE_DOMAIN)
        return true;
    var isYoutubeUrl = parsedUrl.domain() === YOUTUBE_DOMAIN;
    var query = parsedUrl.query();
    return (isYoutubeUrl && query[QUERY_VIDEO_KEY]);
}

function shortenLink(youtubeUrl) { 
    var parsedUrl = Urllib.URL(youtubeUrl);
    var query = parsedUrl.query();
    return 'http://youtu.be/' + query[QUERY_VIDEO_KEY];
}

function isPlayList(youtubeUrl) {
    var parsedUrl = Urllib.URL(youtubeUrl);
    var query = parsedUrl.query();
    return (query[QUERY_PLAYLIST_KEY] !== undefined);
}

String.prototype.toBool = function() {
    return (/^true$/i).test(this);
};