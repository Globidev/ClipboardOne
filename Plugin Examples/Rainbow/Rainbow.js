String.prototype.toBool = function() {
    return (/^true$/i).test(this);
};