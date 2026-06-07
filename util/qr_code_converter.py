import qrcode
encode = qrcode.QRCode()
encode.add_data("https://astro-frontend-six.vercel.app/")
encode.print_ascii()
