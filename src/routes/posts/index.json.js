import fs from 'fs'

export async function get({ params }) {
    let posts = fs.readdirSync("static/posts");

    if (!posts) {
        return {
            body: {
                error: new Error("No posts found")
            }
        }
    }

    return {
        body: {
            posts: posts.map((item) => item.split(".")[ 0 ])
        }
    }
}