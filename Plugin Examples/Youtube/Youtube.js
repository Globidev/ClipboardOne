function isVideo(url) {
    // from http://stackoverflow.com/a/2257257/1592289
    return url.match(/https?:\/\/(?:[a-zA_Z]{2,3}.)?(?:youtube\.com\/watch\?)((?:[\w\d\-\_\=]+&amp;(?:amp;)?)*v(?:&lt;[A-Z]+&gt;)?=([0-9a-zA-Z\-\_]+))/i);
}

function shortenLink(youtubeUrl) { // TODO : Add list check with deny possibility
    var video_id = youtubeUrl.split('v=')[1];
    var ampersandPosition = video_id.indexOf('&');
    if(ampersandPosition != -1)
        video_id = video_id.substring(0, ampersandPosition);
    return 'http://youtu.be/' + video_id;
}

String.prototype.toBool = function() {
    return (/^true$/i).test(this);
};