"""
Use Chrome DevTools Protocol via Python to print the HTML to PDF.
Connects to the already-running Chrome instance.
"""
import json
import base64
import http.client
import ssl
import sys
import os

def get_chrome_ws():
    """Find Chrome's DevTools port and get the WebSocket debugger URL."""
    # Try common CDP ports
    for port in [9222, 9229]:
        try:
            conn = http.client.HTTPConnection("127.0.0.1", port, timeout=2)
            conn.request("GET", "/json")
            resp = conn.getresponse()
            data = json.loads(resp.read())
            for page in data:
                if "an_argument_for_koppa.html" in page.get("url", ""):
                    return page.get("webSocketDebuggerUrl"), page.get("id")
            # Return first page if not found
            if data:
                return data[0].get("webSocketDebuggerUrl"), data[0].get("id")
        except Exception:
            continue
    return None, None

def print_to_pdf_via_http(port, page_id, output_path):
    """Use CDP HTTP endpoint to print a page to PDF."""
    import urllib.request
    
    # Navigate to the HTML file first via CDP
    target_url = "file:///C:/Users/Jimmi/sdt-engine/Papers/an_argument_for_koppa.html"
    
    # Use the /json/protocol to find the page, then use fetch to call Page.printToPDF
    conn = http.client.HTTPConnection("127.0.0.1", port, timeout=30)
    
    # We need to use WebSocket for CDP commands, but let's try a simpler approach
    # Just use the browser's built-in capability
    
    print(f"Found Chrome on port {port}, page {page_id}")
    print("Cannot use CDP printToPDF without WebSocket library.")
    return False

# Alternative: use the HTML file directly with a headless Chrome invocation
def chrome_headless_print(html_path, pdf_path):
    """Use Chrome in headless mode to print to PDF."""
    import subprocess
    
    # Find Chrome
    chrome_paths = [
        r"C:\Program Files\Google\Chrome\Application\chrome.exe",
        r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe",
        os.path.expandvars(r"%LOCALAPPDATA%\Google\Chrome\Application\chrome.exe"),
    ]
    
    chrome = None
    for p in chrome_paths:
        if os.path.exists(p):
            chrome = p
            break
    
    if not chrome:
        # Try to find it via where
        result = subprocess.run(["where", "chrome"], capture_output=True, text=True)
        if result.returncode == 0:
            chrome = result.stdout.strip().split('\n')[0]
    
    if not chrome:
        print("Chrome not found!")
        return False
    
    print(f"Using Chrome at: {chrome}")
    
    file_url = f"file:///{html_path.replace(os.sep, '/')}"
    
    # Run headless Chrome to print to PDF
    cmd = [
        chrome,
        "--headless=new",
        "--disable-gpu",
        "--no-sandbox",
        f"--print-to-pdf={pdf_path}",
        "--print-to-pdf-no-header",
        "--run-all-compositor-stages-before-draw",
        "--virtual-time-budget=15000",
        file_url
    ]
    
    print(f"Running: {' '.join(cmd[:5])}...")
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
    
    if os.path.exists(pdf_path):
        size = os.path.getsize(pdf_path)
        print(f"SUCCESS: PDF created at {pdf_path} ({size:,} bytes)")
        return True
    else:
        print(f"FAILED: {result.stderr}")
        return False

html_path = r"c:\Users\Jimmi\sdt-engine\Papers\an_argument_for_koppa.html"
pdf_path = r"c:\Users\Jimmi\sdt-engine\Papers\an_argument_for_koppa.pdf"

if chrome_headless_print(html_path, pdf_path):
    print("Done!")
else:
    print("Failed to create PDF via headless Chrome.")
