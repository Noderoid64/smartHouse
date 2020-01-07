var optionElement = document.getElementsByTagName("options")[0];
if (optionElement) {
    var timeout = optionElement.getAttribute("timeout");
    if(timeout) {
        setLoading(timeout);
    } else {
        console.log(timeout);
        displayContent();
    }
} else {
    displayContent();
}

function setLoading(time) {
    setTimeout(() => {
        displayContent();
    }, time);
}

function displayContent() {
    document.getElementById("main-content").style.visibility = "visible";
    document.getElementById("main-loader").style.visibility = "hidden";
}

