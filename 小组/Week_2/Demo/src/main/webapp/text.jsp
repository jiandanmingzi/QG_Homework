<!DOCTYPE html>
<html>
<head>
    <title>HTTP Request Tester</title>
    <script>
        function sendRequest() {
            const method = document.getElementById('method').value;
            const url = './textDemo';

            const headers = new Headers();
            headers.append('Responsecode', document.getElementById('ResponseCode').value);
            fetch(url, {
                headers: headers,
                method: method
            })
        }
    </script>
</head>
<body>
    <h1>HTTP Request Tester</h1>
    <form>
        <label for="method">Method:</label>
        <select id="method" name="method">
            <option value="GET">GET</option>
            <option value="POST">POST</option>
            <option value="PUT">PUT</option>
            <option value="DELETE">DELETE</option>
            <option value="HEAD">HEAD</option>
            <option value="OPTIONS">OPTIONS</option>
            <option value="TRACE">TRACE</option>
            <option value="CONNECT">CONNECT</option>
        </select><br><br>
        <label for="ResponseCode">Method:</label>
        <select id="ResponseCode" name="ResponseCode">
            <option value="200">200</option>
            <option value="204">204</option>
            <option value="206">206</option>
            <option value="301">301</option>
            <option value="302">302</option>
            <option value="303">303</option>
            <option value="304">304</option>
            <option value="307">307</option>
            <option value="400">400</option>
            <option value="401">401</option>
            <option value="403">403</option>
            <option value="404">404</option>
            <option value="500">500</option>
            <option value="503">503</option>
        </select><br><br>
    </form>
    <button onclick="sendRequest()">Submit</button>
</body>
</html>