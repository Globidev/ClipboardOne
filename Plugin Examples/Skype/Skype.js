function quote(author, authorName, text, timestamp) {
    return '<quote author="' + author + '" authorname="' + authorName +
           '" timestamp="' + timestamp + '">' + text.toHtml() + 
           '<legacyquote>\r\n\r\n&lt;&lt;&lt; </legacyquote></quote>'
}

Array.prototype.contains = function(element) { // the in operator does not work as expected for some reason ...
    for(var i = 0; i < this.length; i ++)
        if(this[i] === element) return true;
    return false;
};

String.prototype.toHtml = function() {
    return this.replace(/<|>/ig, function(m){
        return '&'+(m =='>'?'g':'l')+'t;';
    })
}