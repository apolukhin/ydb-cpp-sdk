# Generated by devtools/yamaker (pypi).

PY2_LIBRARY()

VERSION(0.16.1)

LICENSE(BSD-3-Clause)

NO_LINT()

NO_CHECK_IMPORTS(
    werkzeug.*
)

PY_SRCS(
    TOP_LEVEL
    werkzeug/__init__.py
    werkzeug/_compat.py
    werkzeug/_internal.py
    werkzeug/_reloader.py
    werkzeug/contrib/__init__.py
    werkzeug/contrib/atom.py
    werkzeug/contrib/cache.py
    werkzeug/contrib/fixers.py
    werkzeug/contrib/iterio.py
    werkzeug/contrib/lint.py
    werkzeug/contrib/profiler.py
    werkzeug/contrib/securecookie.py
    werkzeug/contrib/sessions.py
    werkzeug/contrib/wrappers.py
    werkzeug/datastructures.py
    werkzeug/debug/__init__.py
    werkzeug/debug/console.py
    werkzeug/debug/repr.py
    werkzeug/debug/tbtools.py
    werkzeug/exceptions.py
    werkzeug/filesystem.py
    werkzeug/formparser.py
    werkzeug/http.py
    werkzeug/local.py
    werkzeug/middleware/__init__.py
    werkzeug/middleware/dispatcher.py
    werkzeug/middleware/http_proxy.py
    werkzeug/middleware/lint.py
    werkzeug/middleware/profiler.py
    werkzeug/middleware/proxy_fix.py
    werkzeug/middleware/shared_data.py
    werkzeug/posixemulation.py
    werkzeug/routing.py
    werkzeug/security.py
    werkzeug/serving.py
    werkzeug/test.py
    werkzeug/testapp.py
    werkzeug/urls.py
    werkzeug/useragents.py
    werkzeug/utils.py
    werkzeug/wrappers/__init__.py
    werkzeug/wrappers/accept.py
    werkzeug/wrappers/auth.py
    werkzeug/wrappers/base_request.py
    werkzeug/wrappers/base_response.py
    werkzeug/wrappers/common_descriptors.py
    werkzeug/wrappers/etag.py
    werkzeug/wrappers/json.py
    werkzeug/wrappers/request.py
    werkzeug/wrappers/response.py
    werkzeug/wrappers/user_agent.py
    werkzeug/wsgi.py
)

RESOURCE_FILES(
    PREFIX contrib/python/Werkzeug/py2/
    .dist-info/METADATA
    .dist-info/top_level.txt
    werkzeug/debug/shared/FONT_LICENSE
    werkzeug/debug/shared/console.png
    werkzeug/debug/shared/debugger.js
    werkzeug/debug/shared/jquery.js
    werkzeug/debug/shared/less.png
    werkzeug/debug/shared/more.png
    werkzeug/debug/shared/source.png
    werkzeug/debug/shared/style.css
    werkzeug/debug/shared/ubuntu.ttf
)

END()
